/*CXiaoYingTransitionDetect.h
*
*Reference:
*
*Description: Define XiaoYing transition detect Utils API
*
*chuanchuan.zou  2020/10/15
*
*/

typedef NS_ENUM(NSInteger, ShotType) {
    MUSIC_BEATS = 0,    // 面向音乐卡点视频的卡点检测
    VIDEO_SEG = 1        // 面向视频镜头切分的变化检测
};


@protocol TransitionDetectStateDelegate <NSObject>
- (MVoid) TransitionDetectCallBack : (AMVE_CBDATA_TYPE*) pCBData;
@end


@interface CXiaoYingTransitionDetectUtils : NSObject
{
   
}

/**
 *  Init
 *  @param  pEngine [in] engine
 *  @param type [in] algo type
 *  @return self if success,otherwise return nil
 **/

- (id) init : (CXiaoYingEngine* _Nonnull) pEngine
        transitionType: (ShotType) type; 



/**
 *  Detect transition
 *  @param  input [in] video path
 *  @param pos [in] source range pos
 *  @param len [in] source range len
 *  @return 0 if success,otherwise return error code
 **/

- (MRESULT) DetectTransition : (NSString* _Nonnull) input
                            position: (int) pos
                              length: (int) len;
/**
 * Detect cancel
 **/
- (void) Cancel;

/**
 * Get transition detect result
 * @param result [in] transition detect result array
 * @return MTrue if success, otherwise return MFalse
 **/
- (MBool) GetResult : (NSMutableArray * _Nullable) result;


- (void) SetCallback : (id <TransitionDetectStateDelegate>) statehandler;

@end


