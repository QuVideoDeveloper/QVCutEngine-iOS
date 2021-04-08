/*CXiaoYingSceneClip.h
*
*Reference:
*
*Description: Define XiaoYing CXiaoYingEffectClip  API.
*
*/
@interface CXiaoYingEffectClip : CXiaoYingClip
{
		
}

/**
 *
 * Initialize
 *
 * @param pEngine a instance of CXiaoYingEngine
 * @param pEffect the instance of CXiaoYingEffect
 * @return MERR_NONE if the operation is successful, other value if failed.
 *
 */

- (MRESULT) Init : (CXiaoYingEngine*)pEngine
	      effect : (CXiaoYingEffect *)pEffect;

- (CXiaoYingEffect *) getEffect;
            								 	
@end // CXiaoYingSceneClip

