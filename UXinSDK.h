//
//  UXinSDK.h
//  UXinSDK
//
//  Created by Shaun on 16/2/25.
//  Copyright (c) 2016年 UXIN.COM All rights reserved.

#import <Foundation/Foundation.h>

/**
 *  UXinSDK连接状态
 */
typedef NS_ENUM(NSInteger, UXinSDKStatus) {
    /**
     *  离线
     */
    UXinSDKStatusOffline = 0,
    /**
     *  在线
     */
    UXinSDKStatusOnline = 1,
};

/**
 *  UXinSDK登录模式
 */
typedef NS_ENUM(NSInteger, UXinSDKLoginMode) {
    /**
     *  客户端短信验证方式（手机号、验证码登录）
     */
    UXinSDKLoginModeLocalLogin = 0,
    /**
     *  服务器验证方式（推荐）（第三方app<－>第三方服务端<－>有信服务端登录）
     */
    UXinSDKLoginModeRemoteLogin = 1
};

/**
 *  有信通话时间（单位分钟）
 */
typedef NS_ENUM(int16_t, UXinSDKCallTime) {
    /**
     *  限制拨打，如果开发者想限制用户通话，传0即可
     */
    UXinSDKCallTimeLimit = 0,
    /**
     *  单通电话最大通话时长
     */
    UXinSDKCallTimeMax = INT16_MAX,
};

/**
 *  主叫拨号通话事件
 */
typedef NS_ENUM(NSInteger, UXinSDKCallEvent) {
    /**
     *  正在接通
     */
    UXinSDKCallEventConnecting      = 0,
    /**
     *  正在响铃
     */
    UXinSDKCallEventRinging         = 1,
    /**
     *  已接听
     */
    UXinSDKCallEventAnsered         = 2,
    /**
     *  对方拒接
     */
    UXinSDKCallEventReject          = 3,
    /**
     *  接通后自己挂断
     */
    UXinSDKCallEventHangupBySelf    = 4,
    /**
     *  接通后对方挂断
     */
    UXinSDKCallEventHangupByOther   = 5,
    /**
     *  系统挂断
     */
    UXinSDKCallEventHangupBySystem  = 6,
};

/**
 *  UXinSDK设置
 */
@interface UXinSDKSetting : NSObject

/**
 *  是否震动
 */
@property (nonatomic, assign) BOOL isVibration;

/**
 *  是否播放铃声
 */
@property (nonatomic, assign) BOOL isPlayRing;

@end

/**
 *  UXinSDKDelegate
 */
@protocol UXinSDKDelegate <NSObject>

@optional

/**
 *  SDK连接状态
 *
 *  @param status 见UXinSDKStatus
 */
- (void)uxinSDKstatus:(UXinSDKStatus)status;

/**
 *  token失效或者token不正确，或者没有token。
 *  服务器验证方式（推荐）下用户可以根据此回调方法来重新获取token，然后登录有信服务器
 *  客户端短信验证方式下会自动再次更新token，如更新失败，则需要用户输入手机号验证在次验证登录
 */
- (void)uxinSDKTokenInvalid;

/**
 *  被踢断开连接
 */
- (void)uxinSDKBeKicked;

/**
 *  通话被限制挂断(当开发者对电话时长有限制时，传入了maxtime，当时间到了，电话会被系统自动挂断，此时会回调此方法，开发者可以根据自己的需求去实现定制化的逻辑和页面)
 */
- (void)uxinSDKLimitHangup;

/**
 *  轻量CRM
 *
 *  开发者拿到此CRMId去开发者服务端查询对应的crm信息，然后通过block(CRMString)传入给sdk，sdk进行展示.
 *  CRM信息由开发者自行维护上下文，sdk只做展示
 *
 *  @param CRMId crmid 目前的crmid是主叫手机号
 *  @param block 开发者调用block(CRMString)把crm值传入SDK
 *  @notice CRMString支持部分html标签
 支持的html标签有：
 b标签
 font标签
 i标签
 u标签
 */
- (void)uxinSDKCRM:(NSString*)CRMId CRMString:(void (^)(NSString *CRMString))block;

@end

/**
 *
 *  UXinSDK提供打OTT电话和直拨电话功能，可以作为主叫，也可以作为被叫
 *  名次解释:
 *  OTT电话:UXinSDK拨打UXinSDK、UXin客户端
 *  直拨电话:UXinSDK拨打运营商电话
 */
@interface UXinSDK : NSObject

/**
 *  初始化sdk
 *  此方法用来客户端短信验证方式初始化
 */
+ (BOOL)registerApp:(NSString*)appID appKey:(NSString*)appKey delegate:(id<UXinSDKDelegate>)delegate;

/**
 *  显示登录页面
 */
+ (void)showLoginUI;

/**
 *  添加设置
 */
+ (void)setSetting:(UXinSDKSetting*)setting;


/**
 *  拨打电话
 *  默认是智能呼叫，不录音，不限时。
 
 *  @param strPhoneNumber 被叫号码
 *
 *  @return 调用是否成功
 *  正常返回YES,失败的话返回NO。
 ＃在没有数据网络的情况下，会调用用户系统电话拨打电话，结果返回YES。
 失败则需
 1.检查被叫号码是否正确，
 2.是否调用过registerApp:或registerApp4RemoteMode:方法来初始化sdk
 
 如果调用失败，被叫手机号是正常的，再次登录上有信服务器后，会自动拨打上次未拨打出去的电话
 */
+ (BOOL)callPhoneNumber:(NSString*)strPhoneNumber;

/**
 *  拨打电话（通话时长）
 *  不录音，增加通话时长选项。
 *  @param strPhoneNumber 被叫号码
 *  @param maxTime        该通电话可拨打时间（单位分钟）
 *
 *  @return 调用结果
 */
+ (BOOL)callPhoneNumber:(NSString*)strPhoneNumber maxTime:(UXinSDKCallTime)maxTime;

/**
 *  拨打电话（录音开关、通话时长）
 *
 *  @param strPhoneNumber 被叫号码
 *  @param isRecord       是否需要录音
 *  @param maxTime        该通电话可拨打时间（单位分钟）
 *  @return 调用结果
 */
+ (BOOL)callPhoneNumber:(NSString *)strPhoneNumber
               isRecord:(BOOL)isRecord
                maxTime:(UXinSDKCallTime)maxTime;

/**
 *  拨打电话（带通话状态回调）
 *
 *  @param strPhoneNumber 被叫号码
 *  @param isRecord       是否录音
 *  @param maxTime        该通电话可拨打时间（单位分钟）
 *  @param callEventBlock 通话状态回调
 *  @param event          通话事件见UXinSDKCallEvent
 *  @return 调用结果
 */
+ (BOOL)callPhoneNumber:(NSString *)strPhoneNumber
               isRecord:(BOOL)isRecord
                maxTime:(UXinSDKCallTime)maxTime
         callEventBlock:(void (^)(UXinSDKCallEvent event))callEventBlock;

/**
 *  拨打电话（带通话状态回调、传入默认昵称）
 *
 *  @param strPhoneNumber 被叫号码
 *  @param isRecord       是否录音
 *  @param maxTime        该通电话可拨打时间（单位分钟）
 *  @param callEventBlock 通话状态回调
 *  @param nickName       默认昵称
 *  @param event          通话事件见UXinSDKCallEvent
 *  @return 调用结果
 */
+ (BOOL)callPhoneNumber:(NSString *)strPhoneNumber
               isRecord:(BOOL)isRecord
                maxTime:(UXinSDKCallTime)maxTime
               nickName:(NSString *)nickName
         callEventBlock:(void (^)(UXinSDKCallEvent event))callEventBlock;

/**
 *  SDK版本
 *
 *  @return versionString
 */
+ (NSString *)sdkVersion;

/**
 *  在AppStore中下载有信
 */
+ (void)toAppStoreForUxin;

/**
 *  当前登录状态，online可以直接拨打电话，offline说明没有登录
 */
+ (UXinSDKStatus)currentLoginStatus;

/**
 *  当前登录模式
 */
+ (UXinSDKLoginMode)currentLoginMode;

/**
 *  注销当前用户(清除缓存并且断开连接)
 第三方开发者注销账户使用
 */
+ (void)logout;

/**
 *  更新商家专号
 *  此操作需要先调用registerApp或registerApp4RemoteMode初始化sdk
 *  @return 接口调用是否成功
 */
+ (BOOL)updateVipContacts;

@end

/**
 *  服务器验证方式（推荐）
 *  正常调用步骤：
 1.调用registerApp4RemoteMode，
 2.实现协议方法uxinSDKTokenInvalid
 3.在uxinSDKTokenInvalid方法里面调用开发者服务器接口获取token，
 4.获取成功后调用loginWith:(NSString*)phoneNumber token:(NSString*)token
 5.在需要拨打电话的地方根据需要调用callPhoneNumber
 */
@interface UXinSDK (RemoteMode)

/**
 *  服务器验证方式（推荐）初始化uxinsdk
 *  此方法用来服务器验证方式（推荐）初始化
 */
+ (BOOL)registerApp4RemoteMode:(NSString*)appID appKey:(NSString*)appKey delegate:(id<UXinSDKDelegate>)delegate;

/**
 *  登录有信服务器（服务器验证方式使用）
 *  用户先调用用户服务器，用户服务器调用有信服务器来获取token，把获取到的token和手机号带入sdk登录有信服务器
 此方法异步登录SDK服务器
 *  @param phoneNumber 主叫号码(如果走显号路线，必须传真实手机号码，否则拨打不了电话)
 *  @param token       主叫token（必填）
 */
+ (BOOL)loginWith:(NSString*)phoneNumber token:(NSString*)token;

@end

/**
 *  将在以后的某个版本删除的方法
 */
@interface UXinSDK (Deprecated)

/**
 *  断开连接
 *  为了用户能更方便的拨打有信电话，此方法已经被弃用，将来某个版本会移除。
 *  请用｀+(void)logout｀
 */
+ (void)disconnect;

/**
 *  清除缓存,把本地保存的token清除，下次登录sdk需要重新获取token
 *  请用｀+(void)logout｀
 */
+ (void)clearCache;
@end