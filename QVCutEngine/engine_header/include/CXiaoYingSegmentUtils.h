/*CXiaoYingFaceDTUtils.h
*
*Reference:
*
*Description: Define XiaoYing segment Utils API
*
*jiawei.liu  2020/8/1
*
*/

@interface CXiaoYingSegmentUtils : NSObject
{
   
}

/**
 *  Create segment handle
 *  @param  hAPPContext [in] app context
 *  @param pszModelFilePath [in] model file path
 *  @param pEngine,engine instance
 *  @return 0 if success,otherwise return error code
 **/
- (UInt32) Create : (MHandle _Nullable) hAPPContext
    ModelFilePath : (NSString* _Nonnull)pszModelFilePath
           Engine : (CXiaoYingEngine* _Nonnull) pEngine;

/**
 *  Destroy segment handle
 *  @return	 QVET_ERR_NONE if success,error code if failed
 **/
- (MVoid) DestroyContext;

/**
 * 图像背景分割
 * @param cvImgBuf,用来分割的bitmap
 * @param dwRotation,纹理转正需要旋转的角度
 * @param pMaskBitmap,分割输出的mask
 * @return	 QVET_ERR_NONE if success,error code if failed
 **/
- (MRESULT) GetMaskByBMP : (CVImageBufferRef) cvImgBuf
                Rotation : (MDWord) dwRotation
                    Mask : (MBITMAP*  _Nonnull) pMaskBitmap;


/**
 * 图像背景分割
 * @param pStrImagePath,用来分割的图片的路径
 * @param dwRotation,纹理转正需要旋转的角度
 * @param pMaskBitmap,分割输出的mask
 * @return  QVET_ERR_NONE if success,error code if failed
 **/
- (MRESULT) GetMaskByBMPByImgPath : (NSString*) pStrImagePath
                         Rotation : (MDWord) dwRotation
                             Mask : (MBITMAP*  _Nonnull) pMaskBitmap;


- (MRESULT) GetMaskRectByImgPath: (NSString*) pStrImagePath
								Mask :	(NSString*) pMaskPath
							Rotation :	(MDWord) dwRotation
								Rect :  (MRECT*) pRect;

/**
 * 由bitmap获得该bitmap的点位
 * @param pMaskBitmap[IN]
 * @param pMaskPoints[OUT]
 * 简单描述: 获取到的mask边界点, 不同连通域点位之间用点(num, -100)隔开
 * num为该组点位数目, 数据排布: | Point0=(num1, -100) | num1个点 | Pointx=(num2, -100) | num2个点 | ......  
 **/
- (MRESULT) GetPointFromMask : (MBITMAP* _Nonnull) pMaskBitmap
                      Points : (NSMutableArray * _Nonnull) arrMaskPoints;

/**
*获取 图像中占比超过阈值的对象个数
* @param pMaskBitmap[in],mask bitmap
* @param fThreshold[in],纹理转正需要旋转的角度
* @return  -1,内部出错,>=0,对象个数
**/
- (MRESULT) CheckSegmentNum : (MBITMAP* _Nonnull) pMaskBitmap
                  Threshold : (MFloat) fThreshold;

- (MRESULT) GetRect : (CXIAOYING_RECT*) pRect
             ByMask : (MBITMAP* _Nonnull) pMaskBitmap;
@end // CXiaoYingSegmentUtils


