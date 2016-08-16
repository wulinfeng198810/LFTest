//
//  LTError.h
//  LTClient
//
//  SDK定义的错误
//
//  Created by 吴林峰 on 16/8/8.
//  Copyright © 2016年 WiseUC. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "LTErrorCode.h"

/*!
 *  \~chinese
 *  SDK定义的错误
 *
 *  \~english
 *  SDK defined error
 */
@interface LTError : NSObject

/*!
 *  \~chinese
 *  错误码
 *
 *  \~english
 *  Error code
 */
@property (nonatomic) LTErrorCode code;

/*!
 *  \~chinese
 *  错误描述
 *
 *  \~english
 *  Error description
 */
@property (nonatomic, strong) NSString *errorDescription;


/*!
 *  \~chinese
 *  初始化错误实例
 *
 *  @param aDescription  错误描述
 *  @param aCode         错误码
 *
 *  @result 错误实例
 *
 *  \~english
 *  Initialize a error instance
 *
 *  @param aDescription  Error description
 *  @param aCode         Error code
 *
 *  @result Error instance
 */
- (instancetype)initWithDescription:(NSString *)aDescription
                               code:(LTErrorCode)aCode;

/*!
 *  \~chinese
 *  创建错误实例
 *
 *  @param aDescription  错误描述
 *  @param aCode         错误码
 *
 *  @result 对象实例
 *
 *  \~english
 *  Create a error instance
 *
 *  @param aDescription  Error description
 *  @param aCode         Error code
 *
 *  @result Error instance
 */
+ (instancetype)errorWithDescription:(NSString *)aDescription
                                code:(LTErrorCode)aCode;

@end

