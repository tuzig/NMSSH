//
//  NMSSHChannelStream.h
//  NMSSH
//
//  Created by Nils Bergmann on 04/12/2021.
//

#ifndef NMSSHChannelStream_h
#define NMSSHChannelStream_h

@protocol NMSSHChannelStreamReceiveDelegate <NSObject>

-(void)onStdout: (NSString * _Nonnull)stringText;

-(void)onStderr: (NSString * _Nonnull)stringText;

-(void)onExit: (NSNumber * _Nonnull)exitCode exitSignal:(NSString * _Nullable) exitSignal;

-(void)onError: (NSError * _Nonnull)error;

@end

@interface NMSSHChannelStream : NSObject

@property (nonatomic,strong) id <NMSSHChannelStreamReceiveDelegate> _Nullable delegate;

@end

#endif /* NMSSHChannelStream_h */
