//
//  WiseUCHelper.h
//  WiseUCHelper : 获取本地IP地址、UUID 等工具
//
//  Created by 吴林峰 on 15/10/21.
//  Copyright © 2015年 ___LinFeng___. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface WiseUCHelper : NSObject

#pragma mark - 获取本地 IP 地址
+ (NSString *)deviceIPAdress;

#pragma mark - 获取应用版本
+ (NSString *)applicationVersion;

#pragma mark - 获取应用名称
+ (NSString *)applicationDisplayName;

#pragma mark - 获取IOS系统版本
+ (NSString *)getIOSVersion;

#pragma mark - UUID

#pragma mark -- 获取128位UUID
+ (NSString *)get_128Bytes_UUID;

#pragma mark -- 获取32位UUID
+ (NSString *)get_32Bytes_UUID;

#pragma mark -- 获取字符串 size
+ (CGSize)getNSStringSize:(NSString *)str withFontSize:(CGFloat)fontSize forWidth:(CGFloat)width;

/**
 *  清理缓存
 *
 *  @param complete 回调
 */
+ (void)clearCacheAction:(void(^)(BOOL clearFinished))complete;

/**
 *  缓存大小计算
 *
 *  @return 缓存大小
 */
+ (CGFloat)cacheSize;

// 下载 IMServerCfg 配置文件
+ (void)downloadIMServerCfgWithServerIP:(NSString *)ServerIP complete:(void(^)(NSDictionary *IMServerCfgDict))complete;

/**
 *  解析 ini 文件
 *
 *  @param iniFilePath ini文件路径
 *  @param pragram     待取参数
 *
 *  @return 返回值
 */
+ (NSDictionary *)parseIniFile:(NSString *)iniFilePath pragram:(NSDictionary *)pragram;

@end
