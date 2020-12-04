/*CXiaoYingMultiDetec.h
*
*/

@interface CXiaoYingMultiDetecUtils : NSObject
{
   
}

/**
 *  Create multidetec handle
 *  @param  hAPPContext [in] app context
 *  @param pszModelFilePath [in] model file path
 *  @param pEngine,engine instance
 *  @return 0 if success,otherwise return error code
 **/
- (UInt32) Create : (MHandle _Nullable) hAPPContext
    ModelFilePath : (NSString* _Nonnull)pszModelFilePath
           Engine : (CXiaoYingEngine* _Nonnull) pEngine;

/**
 *  Destroy multidetec handle
 *  @return     QVET_ERR_NONE if success,error code if failed
 **/
- (MVoid) DestroyContext;

/**
*检测图片中是否有人体目标
* @param pBitmap [in] bitmap
* @return  
**/
- (MBool) CheckPersonByBMP : (CVImageBufferRef) cvImgBuf;

@end // CXiaoYingMultiDetecUtils



