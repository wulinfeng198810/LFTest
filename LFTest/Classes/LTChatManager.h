//
//  LTChatManager.h
//  LTClient
//
//  此协议定义了聊天相关操作
//
//  Created by 吴林峰 on 16/8/8.
//  Copyright © 2016年 WiseUC. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "LTChatManagerDelegate.h"
#import "LTConversation.h"

#import "LTMessage.h"
//#import "LTTextMessageBody.h"
//#import "LTLocationMessageBody.h"
//#import "LTCmdMessageBody.h"
//#import "LTFilLTessageBody.h"
//#import "LTImagLTessageBody.h"
//#import "LTVoicLTessageBody.h"
//#import "LTVideoMessageBody.h"

@class LTError;

/*!
 *  \~chinese
 *  聊天相关操作
 *
 *  \~english
 *  Operations of chat
 */
@protocol LTChatManager <NSObject>

@required

#pragma mark - Delegate

/*!
 *  \~chinese
 *  添加回调代理
 *
 *  @param aDelegate  要添加的代理
 *  @param aQueue     执行代理方法的队列
 *
 *  \~english
 *  Add delegate
 *
 *  @param aDelegate  Delegate
 *  @param aQueue     The queue of call delegate method
 */
- (void)addDelegate:(id<LTChatManagerDelegate>)aDelegate
      delegateQueue:(dispatch_queue_t)aQueue;

/*!
 *  \~chinese
 *  移除回调代理
 *
 *  @param aDelegate  要移除的代理
 *
 *  \~english
 *  RLTove delegate
 *
 *  @param aDelegate  Delegate
 */
- (void)rLToveDelegate:(id<LTChatManagerDelegate>)aDelegate;

#pragma mark - Conversation

/*!
 *  \~chinese
 *  获取所有会话，如果内存中不存在会从DB中加载
 *
 *  @result 会话列表<LTConversation>
 *
 *  \~english
 *  Get all conversations, will load conversations from DB if not exist in mLTory
 *
 *  @result Conversation list<LTConversation>
 */
- (NSArray *)getAllConversations;

/*!
 *  \~chinese
 *  从数据库中获取所有的会话，执行后会更新内存中的会话列表
 *
 *  同步方法，会阻塞当前线程
 *
 *  @result 会话列表<LTConversation>
 *
 *  \~english
 *  Load all conversations from DB, will update conversation list in mLTory after this method is called
 *
 *  Synchronization method will block the current thread
 *
 *  @result Conversation list<LTConversation>
 */
- (NSArray *)loadAllConversationsFromDB;

/*!
 *  \~chinese
 *  获取一个会话
 *
 *  @param aConversationId  会话ID
 *  @param aType            会话类型
 *  @param aIfCreate        如果不存在是否创建
 *
 *  @result 会话对象
 *
 *  \~english
 *  Get a conversation
 *
 *  @param aConversationId  Conversation id
 *  @param aType            Conversation type
 *  @param aIfCreate        Whether create conversation if not exist
 *
 *  @result Conversation
 */
- (LTConversation *)getConversation:(NSString *)aConversationId
                               type:(LTConversationType)aType
                   createIfNotExist:(BOOL)aIfCreate;

/*!
 *  \~chinese
 *  删除会话
 *
 *  @param aConversationId  会话ID
 *  @param aDeletLTessage   是否删除会话中的消息
 *
 *  @result 是否成功
 *
 *  \~english
 *  Delete a conversation
 *
 *  @param aConversationId  Conversation id
 *  @param aDeletLTessage   Whether delete messages
 *
 *  @result Whether deleted successfully
 */
- (BOOL)deleteConversation:(NSString *)aConversationId
            deletLTessages:(BOOL)aDeletLTessage;

/*!
 *  \~chinese
 *  删除一组会话
 *
 *  @param aConversations  会话列表<LTConversation>
 *  @param aDeletLTessage  是否删除会话中的消息
 *
 *  @result 是否成功
 *
 *  \~english
 *  Delete multiple conversations
 *
 *  @param aConversations  Conversation list<LTConversation>
 *  @param aDeletLTessage  Whether delete messages
 *
 *  @result Whether deleted successfully
 */
- (BOOL)deleteConversations:(NSArray *)aConversations
             deletLTessages:(BOOL)aDeletLTessage;

/*!
 *  \~chinese
 *  导入一组会话到DB
 *
 *  @param aConversations  会话列表<LTConversation>
 *
 *  @result 是否成功
 *
 *  \~english
 *  Import multiple conversations to DB
 *
 *  @param aConversations  Conversation list<LTConversation>
 *
 *  @result Whether imported successfully
 */
- (BOOL)importConversations:(NSArray *)aConversations;

#pragma mark - Message

/*!
 *  \~chinese
 *  获取消息附件路径, 存在这个路径的文件，删除会话时会被删除
 *
 *  @param aConversationId  会话ID
 *
 *  @result 附件路径
 *
 *  \~english
 *  Get message attachment path for the conversation, files in this path will also be deleted when delete the conversation
 *
 *  @param aConversationId  Conversation id
 *
 *  @result Attachment path
 */
- (NSString *)getMessageAttachmentPath:(NSString *)aConversationId;

/*!
 *  \~chinese
 *  导入一组消息到DB
 *
 *  @param aMessages  消息列表<LTMessage>
 *
 *  @result 是否成功
 *
 *  \~english
 *  Import multiple messages
 *
 *  @param aMessages  Message list<LTMessage>
 *
 *  @result Whether imported successfully
 */
- (BOOL)importMessages:(NSArray *)aMessages;

/*!
 *  \~chinese
 *  更新消息到DB
 *
 *  @param aMessage  消息
 *
 *  @result 是否成功
 *
 *  \~english
 *  Update message to DB
 *
 *  @param aMessage  Message
 *
 *  @result Whether updated successfully
 */
- (BOOL)updatLTessage:(LTMessage *)aMessage;

/*!
 *  \~chinese
 *  发送消息已读回执
 *
 *  异步方法
 *
 *  @param aMessage  消息
 *
 *  \~english
 *  Send read ack for message
 *
 *  Asynchronous methods
 *
 *  @param aMessage  Message instance
 */
- (void)asyncSendReadAckForMessage:(LTMessage *)aMessage;

/*!
 *  \~chinese
 *  发送消息
 *
 *  异步方法
 *
 *  @param aMessage            消息
 *  @param aProgressCompletion 附件上传进度回调block
 *  @param aCompletion         发送完成回调block
 *
 *  \~english
 *  Send a message
 *
 *  Asynchronous methods
 *
 *  @param aMessage            Message instance
 *  @param aProgressCompletion The block of attachment upload progress
 *
 *  @param aCompletion         The block of send complete
 */
- (void)asyncSendMessage:(LTMessage *)aMessage
                progress:(void (^)(int progress))aProgressCompletion
              completion:(void (^)(LTMessage *message,
                                   LTError *error))aCompletion;

/*!
 *  \~chinese
 *  重发送消息
 *
 *  异步方法
 *
 *  @param aMessage            消息
 *  @param aProgressCompletion 附件上传进度回调block
 *  @param aCompletion         发送完成回调block
 *
 *  \~english
 *  Resend Message
 *
 *  Asynchronous methods
 *
 *  @param aMessage            Message instance
 *  @param aProgressCompletion The callback block of attachment upload progress
 *  @param aCompletion         The callback block of send complete
 */
- (void)asyncResendMessage:(LTMessage *)aMessage
                  progress:(void (^)(int progress))aProgressCompletion
                completion:(void (^)(LTMessage *message,
                                     LTError *error))aCompletion;

/*!
 *  \~chinese
 *  下载缩略图（图片消息的缩略图或视频消息的第一帧图片），SDK会自动下载缩略图，所以除非自动下载失败，用户不需要自己下载缩略图
 *
 *  异步方法
 *
 *  @param aMessage            消息
 *  @param aProgressCompletion 附件下载进度回调block
 *  @param aCompletion         下载完成回调block
 *
 *  \~english
 *  Download message thumbnail attachments (thumbnails of image message or first frame of video image), SDK can download thumbail automatically, so user should NOT download thumbail manually except automatic download failed
 *
 *  Asynchronous methods
 *
 *  @param aMessage            Message instance
 *  @param aProgressCompletion The callback block of attachment download progress
 *  @param aCompletion         The callback block of download complete
 */
- (void)asyncDownloadMessageThumbnail:(LTMessage *)aMessage
                             progress:(void (^)(int progress))aProgressCompletion
                           completion:(void (^)(LTMessage * message,
                                                LTError *error))aCompletion;

/*!
 *  \~chinese
 *  下载消息附件（语音，视频，图片原图，文件），SDK会自动下载语音消息，所以除非自动下载语音失败，用户不需要自动下载语音附件
 *
 *  异步方法
 *
 *  @param aMessage            消息
 *  @param aProgressCompletion 附件下载进度回调block
 *  @param aCompletion         下载完成回调block
 *
 *  \~english
 *  Download message attachment(voice, video, image or file), SDK can download voice automatically, so user should NOT download voice manually except automatic download failed
 *
 *  Asynchronous methods
 *
 *  @param aMessage            Message instance
 *  @param aProgressCompletion The callback block of attachment download progress
 *  @param aCompletion         The callback block of download complete
 */
- (void)asyncDownloadMessageAttachments:(LTMessage *)aMessage
                               progress:(void (^)(int progress))aProgressCompletion
                             completion:(void (^)(LTMessage *message,
                                                  LTError *error))aCompletion;


@end