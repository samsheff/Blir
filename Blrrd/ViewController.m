//
//  ViewController.m
//  Blrrd
//
//  Created by Sam Sheffres on 9/22/14.
//  Copyright (c) 2014 Sam Sheffres. All rights reserved.
//

#import "ViewController.h"

#import <QuartzCore/QuartzCore.h>
# include <AssetsLibrary/AssetsLibrary.h>

#define DEGREES_TO_RADIANS(angle) ((angle) / 180.0 * M_PI)

@interface ViewController ()

@end

@implementation ViewController

#pragma mark View Controller Methods

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)viewWillAppear:(BOOL)animated
{
    [self displayButtonViews:NO];
    
    CAGradientLayer *backgroundLayer = [self createGradientLayer];
    backgroundLayer.frame = self.view.frame;
    [self.view.layer insertSublayer:backgroundLayer atIndex:0];
    
    self.blurImageView.image = [self createBlurLayerWithIntensity:25.0f];
    
    [self displayButtonViews:YES];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark IB Actions

- (IBAction)regenerateGradient:(id)sender
{
    [self displayButtonViews:NO];
    
    CABasicAnimation *crossFade = [CABasicAnimation animationWithKeyPath:@"contents"];
    crossFade.duration = 2.0;
    crossFade.fromValue = (__bridge id)(self.blurImageView.image.CGImage);
    
    self.blurImageView.image = nil;
    
    NSMutableArray *layers = [self.view.layer.sublayers mutableCopy];
    [layers removeObjectAtIndex:(NSUInteger)0];
    self.view.layer.sublayers = [layers copy];
    
    CAGradientLayer *backgroundLayer = [self createGradientLayer];
    backgroundLayer.frame = self.view.frame;
    
    [self.view.layer insertSublayer:backgroundLayer atIndex:0];
    
    self.blurImageView.image = [self createBlurLayerWithIntensity:30.0f];
    
    crossFade.toValue = (__bridge id)(self.blurImageView.image.CGImage);
    [self.blurImageView.layer addAnimation:crossFade forKey:@"animateContents"];
    
    [self displayButtonViews:YES];
}

- (IBAction)onTapSavePhoto:(id)sender
{
    ALAuthorizationStatus status = [ALAssetsLibrary authorizationStatus];
    
    UIImageWriteToSavedPhotosAlbum(self.blurImageView.image, nil, nil, nil);
    
    if (status == ALAuthorizationStatusDenied && status != ALAuthorizationStatusNotDetermined) {
        [self showImagePermissionsErrorAlert];
    } else if (status == ALAuthorizationStatusAuthorized){
        [self showImageSavedAlert];
    }
}

#pragma mark Gradients

- (CAGradientLayer*)createGradientLayer
{
    
    UIColor *topColor = [self generateRandomColor];
    UIColor *topMiddleColor = [self generateRandomColor];
    UIColor *middleColor = [self generateRandomColor];
    UIColor *bottomMiddleColor = [self generateRandomColor];
    UIColor *bottomColor = [self generateRandomColor];

    NSArray *gradientColors = [NSArray arrayWithObjects:(id)topColor.CGColor, (id)topMiddleColor.CGColor, (id)middleColor.CGColor, (id)bottomMiddleColor.CGColor, (id)bottomColor.CGColor, nil];
    NSArray *gradientLocations = [NSArray arrayWithObjects:[NSNumber numberWithInt:0.0], [NSNumber numberWithInt:0.30], [NSNumber numberWithInt:0.55], [NSNumber numberWithInt:0.80], [NSNumber numberWithInt:1.0], nil];
    
    CAGradientLayer *gradientLayer = [CAGradientLayer layer];
    gradientLayer.colors = gradientColors;
    gradientLayer.locations = gradientLocations;
    
    CATransform3D layerTransform = gradientLayer.transform;
    
    gradientLayer.transform = CATransform3DRotate(layerTransform, DEGREES_TO_RADIANS(arc4random_uniform(360)), 0, 0, 0);
//    gradientLayer.transform = CATransform3DScale(layerTransform, arc4random_uniform(2), arc4random_uniform(3), 0);

    return gradientLayer;
}

#pragma mark Blur
- (UIImage*)createBlurLayerWithIntensity:(CGFloat)intensity
{
    //Get a screen capture from the current view.
    UIGraphicsBeginImageContext(self.view.bounds.size);
    [self.view.layer renderInContext:UIGraphicsGetCurrentContext()];
    UIImage *viewImg = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    //Blur the image
    CIImage *blurImg = [CIImage imageWithCGImage:viewImg.CGImage];
    
    CGAffineTransform transform = CGAffineTransformIdentity;
    CIFilter *clampFilter = [CIFilter filterWithName:@"CIAffineClamp"];
    [clampFilter setValue:blurImg forKey:@"inputImage"];
    [clampFilter setValue:[NSValue valueWithBytes:&transform objCType:@encode(CGAffineTransform)] forKey:@"inputTransform"];
    
    CIFilter *gaussianBlurFilter = [CIFilter filterWithName: @"CIGaussianBlur"];
    [gaussianBlurFilter setValue:clampFilter.outputImage forKey: @"inputImage"];
    [gaussianBlurFilter setValue:[NSNumber numberWithFloat:intensity] forKey:@"inputRadius"];
    
    CIContext *context = [CIContext contextWithOptions:nil];
    CGImageRef cgImg = [context createCGImage:gaussianBlurFilter.outputImage fromRect:[blurImg extent]];
    UIImage *outputImg = [UIImage imageWithCGImage:cgImg];
    
    return outputImg;
}

#pragma mark Color

- (UIColor*)generateRandomColor
{
    return [UIColor colorWithRed:(CGFloat)arc4random_uniform(255)/255
                    green:(CGFloat)arc4random_uniform(255)/255
                     blue:(CGFloat)arc4random_uniform(255)/255
                    alpha:1];

}

#pragma mark Alerts
- (void)showImageSavedAlert
{
    UIAlertView *savedAlert = [[UIAlertView alloc] initWithTitle:@"Saved!" message:@"The wallpaer was saved to your photos." delegate:self cancelButtonTitle:@"Got it!" otherButtonTitles:nil];
    
    [savedAlert show];
}

- (void)showImagePermissionsErrorAlert
{
    UIAlertView *notSavedAlert = [[UIAlertView alloc] initWithTitle:@"Error" message:@"Blir doesn't have permission to your photos! Go change your settings and try again." delegate:self cancelButtonTitle:@"Got it!" otherButtonTitles:nil];
    
    [notSavedAlert show];
}

#pragma mark Button Visibility

- (void)displayButtonViews:(BOOL)active
{
    if (active) {
        self.buttonView.hidden = NO;
        self.logo.hidden = NO;
        self.saveButtonView.hidden = NO;
    } else {
        self.buttonView.hidden = YES;
        self.logo.hidden = YES;
        self.saveButtonView.hidden = YES;
    }
}
@end
