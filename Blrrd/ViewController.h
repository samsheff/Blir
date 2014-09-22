//
//  ViewController.h
//  Blrrd
//
//  Created by Sam Sheffres on 9/22/14.
//  Copyright (c) 2014 Sam Sheffres. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController

@property (strong, nonatomic) IBOutlet UIImageView *buttonView;
@property (strong, nonatomic) IBOutlet UIImageView *saveButtonView;
@property (strong, nonatomic) IBOutlet UIImageView *blurImageView;
@property (strong, nonatomic) IBOutlet UIImageView *logo;

- (IBAction)regenerateGradient:(id)sender;

@end

