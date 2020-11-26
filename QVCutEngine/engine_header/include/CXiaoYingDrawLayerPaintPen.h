/*CXiaoYingDrawLayerPaintPen
*
*Reference:
*
*Description: Define XiaoYing Effect  API. by chenglong 2020/11/14
*
*/

@interface CXiaoYingDrawLayerPaintPen : NSObject {
    
}
/*
 typedef enum {
     EU_DRAW_PAINT_DEFAULT = 0,//默认是铅笔
     EU_DRAW_PAINT_PENCIL = 0,//铅笔
     EU_DRAW_PAINT_PEN=1,//钢笔
     EU_DRAW_PAINT_WATER_PEN=2,//水笔
     EU_DRAW_PAINT_BRUSH=3,//笔刷
     EU_DRAW_PAINT_MARK_PEN=4,//马克笔
     EU_DRAW_PAINT_ERASURE = 5,//擦除
     EU_DRAW_PAINT_END
 }EU_DRAW_PAINT_TYPE;
 **/
@property(nonatomic, readwrite) MDWord dwPenType;//EU_DRAW_PAINT_TYPE 的类型
@property(nonatomic, readwrite) MDWord dwLineColor;//线条的颜色
@property(nonatomic, readwrite) MDWord dwLineType;//0 实线 1 虚线
@property(nonatomic, readwrite) MFloat fLineThickness;//线条的粗细程度, 相对于底图的百分比，例如底图宽度720， 真实的Thickness=720*fLineThickness
@property(nonatomic, readwrite) MFloat fDottedLine;//相对于底图的百分比 例如底图宽度720， 真实的虚线的长度是=720*fDottedLine
@property(nonatomic, readwrite) MBool  bEnableLight;//是否开启发光
@property(nonatomic, readwrite) MFloat fLightRadius;//发光的宽度， 相对于底图的百分比 例如底图宽度720， 真实的发光半径是=720*fLightRadius
@property(nonatomic, readwrite) MDWord dwLightColor;//发光的颜色
@property(nonatomic, readwrite) MFloat fEdgeFeathering;//边缘羽化程度 0~100；

- (MRESULT)convertToCStruct : (MHandle)hType;

@end
