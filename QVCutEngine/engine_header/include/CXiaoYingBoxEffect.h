/*CXiaoYingBoxEffect.h
*
*Reference:
*
*Description: Define XiaoYing CXiaoYingBoxEffect  API.
*
*/
@interface CXiaoYingBoxEffect : CXiaoYingEffect
{
		
}

- (NSObject *) getExternSource;

- (MRESULT) setExternSource:(NSObject *)pSource;
            						
- (MRESULT) clearExternSource;
  
- (MRESULT) switchEffectStatus:(MBool) bStatus;

- (MBool) getEffectStatus;

- (MRESULT) insertEffect:(CXiaoYingEffect*) pEffect Index:(MDWord)index;

- (MRESULT) moveEffect:(CXiaoYingEffect*) pEffect Index:(MDWord)index;

- (MRESULT) deleteEffect:(CXiaoYingEffect*) pEffect;

-(CXiaoYingEffect*)getEffectByUuid:(NSString*)pUUid;

-(CXiaoYingEffect*)getEffectByIndex:(MDWord)dwIndex;
@end // CXiaoYingSceneClip

