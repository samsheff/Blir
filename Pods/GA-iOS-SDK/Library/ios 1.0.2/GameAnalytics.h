//
//  GameAnalytics.h
//  GameAnalytics
//
//  Created by Rick Chapman on 10/02/2014.
//  Copyright (c) 2014 Rick Chapman. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum GASeverityType : NSInteger {
    GASeverityTypeCritical  = 0,
    GASeverityTypeError     = 1,
    GASeverityTypeWarning   = 2,
    GASeverityTypeInfo      = 3,
    GASeverityTypeDebug     = 4,
} GASeverityType;

#define GA_SDK_VERSION  @"ios 1.0.2"

@interface GameAnalytics : NSObject

/**
 * Initialise the GameAnalytics engine. It is recommended that you call
 * this method from the your application delegate in application:didFinishLaunchingWithOptions:
 * Uses the value of 'CFBundleVersion' from the application's info.plist file as the
 * build version of the application by default.
 *
 * @param gameKey
 *            game key supplied when you registered at GameAnalytics
 * @param secretKey
 *            secret key supplied when you registered at GameAnalytics
 */
+ (void)initializeWithGameKey:(NSString *)gameKey secretKey:(NSString *)secretKey;

/**
 * Initialise the GameAnalytics engine. It is recommended that you call
 * this method from the your application delegate in application:didFinishLaunchingWithOptions:
 *
 * @param gameKey
 *            game key supplied when you registered at GameAnalytics
 * @param secretKey
 *            secret key supplied when you registered at GameAnalytics
 * @param build
 *            name supplied by you to identify this build of your app
 *
 * @see initializeWithGameKey:(NSString *)gameKey secretKey:(NSString *)secretKey
 */
+ (void)initializeWithGameKey:(NSString *)gameKey secretKey:(NSString *)secretKey build:(NSString *)build;

/**
 * Enable/disable the inbuilt Uncaught Exception Handler
 *
 * For iOS applications, Apple only allows you to register one crash handler in your app at a time 
 * which means you can only run a single Crash Reporting service. Our Crash Handler feature is disabled 
 * by default, so if you are using another service and do not want to use this Crash Handler instead you 
 * should leave it disabled and you will get the normal Game Analytics service without Crash. If you
 * want to use this Crash Analytics just enable it when you integrate the SDK.
 *
 * We strongly recommend that developers do not install any uncaught exception handlers in their app if
 * they enable this feature.
 *
 * This call must be made before initializeWithGameKey:secretKey:
 *
 * @param value
 *            true = enabled; false = disabled (default = false)
 */
+ (void)enableExceptionHandler:(BOOL)value;

// Events Logging

/**
 * Add a new business event to the event stack. This will be sent off in a
 * batched array after the time interval set using setSendEventsInterval.
 *
 * @param eventId
 *            use colons to denote subtypes, e.g. 'PurchaseWeapon:Shotgun'
 * @param currency
 *            3 digit code for currency e.g. 'USD'
 * @param amount
 *            value of transaction
 * @param area
 *            area/level associated with the event
 * @param x
 *            position on x-axis
 * @param y
 *            position on y-axis
 * @param z
 *            position on z-axis
 */
+ (void)newBusinessEventWithId:(NSString *)eventId currency:(NSString *)currency amount:(NSNumber *)amount area:(NSString *)area x:(NSNumber *)x y:(NSNumber *)y z:(NSNumber *)z;

/**
 * Add a new business event to the event stack. This will be sent off in a
 * batched array after the time interval set using setSendEventsInterval. The
 * current bundle display name will be used as the 'area' value for the event.
 *
 * @param eventId
 *            use colons to denote subtypes, e.g. 'PurchaseWeapon:Shotgun'
 * @param currency
 *            3 digit code for currency e.g. 'USD'
 * @param amount
 *            value of transaction
 */
+ (void)newBusinessEventWithId:(NSString *)eventId currency:(NSString *)currency amount:(NSNumber *)amount;

/**
 * Add a new design event to the event stack. This will be sent off in a
 * batched array after the time interval set using setSendEventsInterval.
 *
 * @param eventId
 *            use colons to denote subtypes, e.g. 'PickedUpAmmo:Shotgun'
 * @param value
 *            numeric value associated with event e.g. number of shells
 * @param area
 *            area/level associated with the event
 * @param x
 *            position on x-axis
 * @param y
 *            position on y-axis
 * @param z
 *            position on z-axis
 */
+ (void)newDesignEventWithId:(NSString *)eventId value:(NSNumber *)value area:(NSString *)area x:(NSNumber *)x y:(NSNumber *)y z:(NSNumber *)z;

/**
 * Add a new design event to the event stack. This will be sent off in a
 * batched array after the time interval set using setSendEventsInterval. The
 * current bundle display name will be used as the 'area' value for the event.
 *
 * @param eventId
 *            use colons to denote subtypes, e.g. 'PickedUpAmmo:Shotgun'
 * @param value
 *            numeric value associated with event e.g. number of shells
 */
+ (void)newDesignEventWithId:(NSString *)eventId value:(NSNumber *)value;

/**
 * Add a new design event to the event stack. This will be sent off in a
 * batched array after the time interval set using setSendEventsInterval. The
 * current bundle display name will be used as the 'area' value for the event.
 *
 * @param eventId
 *            use colons to denote subtypes, e.g. 'PickedUpAmmo:Shotgun'
 */
+ (void)newDesignEventWithId:(NSString *)eventId;

/**
 * Add a new error event to the event stack. This will be sent off in a
 * batched array after the time interval set using setSendEventsInterval.
 *
 * @param message
 *            message associated with the error e.g. the stack trace
 * @param severity
 *            severity of error, use a valid GASeverityType value
 * @param area
 *            area/level associated with the event
 * @param x
 *            position on x-axis
 * @param y
 *            position on y-axis
 * @param z
 *            position on z-axis
 *
 */
+ (void)newErrorEventWithMessage:(NSString *)message severity:(GASeverityType)severity area:(NSString *)area x:(NSNumber *)x y:(NSNumber *)y z:(NSNumber *)z;

/**
 * Add a new error event to the event stack. This will be sent off in a
 * batched array after the time interval set using setSendEventsInterval. The
 * current bundle display name will be used as the 'area' value for the event.
 *
 * @param message
 *            message associated with the error e.g. the stack trace
 * @param severity
 *            severity of error, use a valid GASeverityType value
 * @see setSendEventsInterval
 */
+ (void)newErrorEventWithMessage:(NSString *)message severity:(GASeverityType)severity;

/**
 * Send user info to the Game Analytics server. All parameters are optional,
 * pass in 'null' if you do not have the data.
 *
 * @param gender
 *            user gender, use 'm' for male, 'f' for female
 * @param birthYear
 *            four digit birth year
 * @param friendCount
 *            number of friends
 */
+ (void)setUserInfoWithGender:(NSString *)gender birthYear:(NSNumber *)birthYear friendCount:(NSNumber *)friendCount;

/**
 * Manually send referral info to the Game Analytics server. All parameters
 * are optional, use 'null' if you do not have the data.
 *
 * @param installPublisher
 *            e.g. FB, Chartboost, Google Adwords, Organic
 * @param installSite
 *            e.g. FB.com, FBApp, AppId
 * @param installCampaign
 *            e.g. Launch, EasterBoost, ChrismasSpecial
 * @param installAd
 *            e.g. Add#239823, KnutsShinyAd
 * @param installKeyword
 *            e.g. rts mobile game
 */
+ (void)setReferralInfoWithPublisher:(NSString *)installPublisher installSite:(NSString *)installSite installCampaign:(NSString *)installCampaign installAdgroup:(NSString *)installAdgroup installAd:(NSString *)installAd installKeyword:(NSString *)installKeyword;

// Various settings

/**
 * @brief Set debug log level
 *
 * Set debug log level. Use TRUE while you are developing
 * to see when every event is created and batched to server.
 * Set to FALSE when you release your application so only
 * warning and event log entries are made. The default value is FALSE
 *
 * @param level
 *            Set to TRUE for verbose logs
 *
 * @since SDK Version 1.0.0
 */
+ (void)setDebugLogLevelVerbose:(BOOL)level;

/**
 * Enable/disable automatic batching. By default (true) events are sent off
 * to the GA server after a time interval set using setSendEventsInterval().
 * If disabled (false) then you will need to use manualBatch() to send the
 * events to the server.
 *
 * @param value
 *            true = enabled; false = disabled
 */
+ (void)setAutoBatch:(BOOL)value;

/**
 * Manually send a batch of events. This event will not
 * wait for the sendEventInterval nor will it poll the internet connection.
 * If there is no connection it will simply return.
 */
+ (void)manualBatch;

/**
 * Enable/disable local caching. By default (true) events are cached locally
 * so that even if an internet connection is not available, they will be
 * sent to the GA server when it is restored. If disabled (false) events
 * will be discarded if a connection is unavailable.
 *
 * @param value
 *            true = enabled; false = disabled
 */
+ (void)setLocalCaching:(BOOL)value;

/**
 * Set the amount of time, in seconds, for a session to timeout so that
 * a new one is started when the application is restarted. The
 * default is 20 seconds.
 *
 * @param seconds
 *            interval in seconds
 */
+ (void)setSessionTimeOut:(NSTimeInterval)seconds;

/**
 * Set the amount of time, in seconds, between each batch of events
 * being sent. The default is 20 seconds.
 *
 * @param seconds
 *            interval in seconds
 */
+ (void)setSendEventsInterval:(NSTimeInterval)seconds;

/**
 * Manually clears the database, will result in loss of analytics data if
 * used in production.
 */
+ (void)clearDatabase;

/**
 * Set maximum number of events that are stored locally. Additional events
 * will be discarded. Set to 0 for unlimited (default).
 *
 * @param max
 *            maximum number of events that can be stored
 */
+ (void)setMaximumEventStorage:(NSInteger)maxEvents;

// Frames per second logging

/**
 * Place somewhere inside your draw loop to log FPS. If you are using openGL
 * then that will be inside your Renderer class' onDrawFrame() method. You
 * must then call stopLoggingFPS: at some point to collate the data and
 * send it to GameAnalytics. You can either do this intermittently e.g.
 * every 1000 frames, or over an entire gameplay session e.g. in the
 * UIApplication delegate applicationWillResignActive method. 
 * Either way, the average FPS will be logged.
 *
 */
+ (void)logFPS;

/**
 * Call this method when you want to collate you FPS and send it to the
 * server. You can either do this intermittently e.g. every 1000 frames, or
 * over an entire gameplay session e.g. in the application delegate's applicationWillResignActive: method.
 * Either way, the average FPS will be logged. The parameters are optional.
 * If left out, the name of the current activity will be logged as the area
 * parameter.
 *
 * @param area
 *            (optional - use to log the FPS in a specific level/area)
 * @param x
 *            (optional)
 * @param y
 *            (optional)
 * @param z
 *            (optional)
 */
+ (void)stopLoggingFPSForArea:(NSString *)area x:(NSNumber *)x y:(NSNumber *)y z:(NSNumber *)z;

+ (void)stopLoggingFPS;

/**
 * Set the critical FPS limit. If the average FPS over a period is under
 * this value then a "FPSCritical" design event will be logged. The default
 * is 20 frames per second.
 *
 * @param criticalFPS
 *            in frames per second
 */
+ (void)setCriticalFPSLimit:(NSNumber *)criticalFPS;

/**
 * Set the minimum time period for an average FPS to be logged. This stops
 * spurious results coming from very short time periods. Default is 5
 * seconds.
 *
 * @param minimumTimePeriod
 *            in seconds
 */
+ (void)setMinimumFPSTimePeriod:(NSTimeInterval)minimumTimePeriod;

/**
 * The userId that the SDK uses to track each individual user on the server.
 *
 * @return the user id or null if the SDK is not initialised.
 */
+ (NSString *)getUserID;

/**
 * Set a custom userId string to be attached to all subsequent events. By
 * default, the user ID is generated from the unique identifiers built in to the os.
 *
 * @param userId
 *            Custom unique user ID
 */
+ (void)setUserID:(NSString *)userID;

/**
 * Force a new session to be started by creating a new sessionID. Normally this will not be required.
 *
 */
+ (void)updateSessionID;

@end

extern NSString *k_GA_LoggerMessageNotification;

