/*CXiaoyingAudioAnalyzer.h
*
*Reference:
*
*Description: Define XiaoYing Audio analyzer  API.
*
*/

/**
 * audio analyzer state call back delegate
 * pCBData,data type is AA_ProcessCB_Data*
 */
@protocol AudioAnalyzerStateDelegate <NSObject>
- (MVoid) AudioAnalyzerStateCallBack : (MVoid*) pCBData;
@end

@interface CXiaoyingAudioAnalyzer : NSObject
{
    @protected
    MHandle _hAA;
}
@property(readwrite, nonatomic) MHandle hAA;

/**
 * 
 * Initializes audio analyzer.
 * 
 * @param pInitParam audio analyzer init param
 * @param pStrAVConfig 音频解析参数配置文件
 * @param stateDelegate audio analyzer state delegate.
 * @return MERR_NONE if the operation is successful, other value if failed.
 * 
 */
 
- (MRESULT) Init : (AA_INIT_PARAM*)pInitParam
                   AVConfig : (NSString*)pStrAVConfig
                   StateDelegate : (id <AudioAnalyzerStateDelegate>)stateDelegate;



/**
 *
 * UnInit audio analyzer.
 *
 * @return MERR_NONE if the operation is successful, other value if failed.
 *
 */
- (MRESULT) UnInit;

/**
*
* 从解析得到的json文件获取onset 点信息
*@param pStrResFile json文件路径
*@param pRange 解析audio range
*
* @return float类型的数据，表示Onset时间点，单位ms
*
*/
+ (NSArray<NSNumber*>* _Nullable) GetOnsetDetectResult : (NSString*)pStrResFile
                                             AudioRange: (CXIAOYING_POSITION_RANGE_TYPE*)pRange;

@end // CXiaoyingAudioAnalyzer

