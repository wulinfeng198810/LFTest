//
//  LTMessageBody.m
//  LTClient
//
//  消息体类型的基类
//
//  Created by 吴林峰 on 16/8/8.
//  Copyright © 2016年 WiseUC. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CGGeometry.h>

/*!
 *  \~chinese
 *  消息体类型
 *
 *  \~english
 *  Message body type
 */
typedef enum {
    LTMessageBodyTypeText   = 1,    /*! \~chinese 文本类型 \~english Text */
    LTMessageBodyTypeImage,         /*! \~chinese 图片类型 \~english Image */
    LTMessageBodyTypeVideo,         /*! \~chinese 视频类型 \~english Video */
    LTMessageBodyTypeLocation,      /*! \~chinese 位置类型 \~english Location */
    LTMessageBodyTypeVoice,         /*! \~chinese 语音类型 \~english Voice */
    LTMessageBodyTypeFile,          /*! \~chinese 文件类型 \~english File */
    LTMessageBodyTypeCmd,           /*! \~chinese 命令类型 \~english Cmd */
} LTMessageBodyType;

/*!
 *  \~chinese
 *  消息体
 *
 *  \~english
 *  Message body
 */
@interface LTMessageBody : NSObject

/*!
 *  \~chinese
 *  消息体类型
 *
 *  \~english
 *  Message body type
 */
@property (nonatomic, readonly) LTMessageBodyType type;

@end
