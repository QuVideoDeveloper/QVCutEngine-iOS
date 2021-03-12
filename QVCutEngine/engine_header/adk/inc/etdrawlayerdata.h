#ifndef _VE_LAYER_DATA_H__
#define _VE_LAYER_DATA_H__
#define QVET_DRAW_PROP_RENDER_ENGINE 0x1100

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

typedef enum {
	EU_DRAW_LINE_DEFAULT = 0,//实线
	EU_DRAW_LINE_NORMAL = 0,//实线
	EU_DRAW_LINE_DOTTED = 1,//虚线
	EU_DRAW_LINE_END
}EU_DRAW_LINE_TYPE;

typedef enum {
	EU_DRAW_SHAPE_DEFAULT = 0,//默认线条
	EU_DRAW_SHAPE_LINE = 1,//默认线条
	EU_DRAW_SHAPE_ERASURE = 2,//擦除
	EU_DRAW_SHAPE_LASSO = 3,//套索
	EU_DRAW_SHAPE_PAINT = 4,//涂料/填充
	EU_DRAW_SHAPE_END
}EU_DRAW_SHAPE_TYPE;

/***********************************画笔*****************************/
typedef struct _tag_qvet_draw_paint_base_type//基础类型，描述以后可能使用到画笔类型
{
	OVERLOAD_OPERATOR_NEW
	_tag_qvet_draw_paint_base_type()
	{
		euType = EU_DRAW_PAINT_DEFAULT;//画笔类型，0 铅笔， 1 钢笔等等
	}
	virtual ~_tag_qvet_draw_paint_base_type()
	{

	}
	EU_DRAW_PAINT_TYPE euType;
}QVET_DRAW_PAINT_BASE_TYPE;

typedef struct _tag_qvet_draw_pen_type :public _tag_qvet_draw_paint_base_type
{
	_tag_qvet_draw_pen_type()
	{
		euType = EU_DRAW_PAINT_PENCIL;
		dwLineColor = 0xffffffff;
		dwLineType = 0;
		fLineThickness = 0.01f;
		fLightRadius = 0.02f;
		fDottedLine = 0.01f;
		bEnableLight = MFalse;
		dwLightColor = 0xffffffff;
		fEdgeFeathering = 0.015f;
		bStatus = MFalse;
	}

	MBool operator ==(struct _tag_qvet_draw_pen_type &pen)
	{
		MBool bResult = MFalse;
		if (dwLineColor != pen.dwLineColor \
			|| dwLineType != pen.dwLineType \
			|| dwLightColor != pen.dwLightColor \
			|| bEnableLight != pen.bEnableLight \
			|| fabs(fLineThickness - pen.fLineThickness) > 0.00001 \
			|| fabs(fDottedLine - pen.fDottedLine) > 0.00001 \
			|| fabs(fLightRadius - pen.fLightRadius) > 0.00001 \
			|| bStatus != pen.bStatus
			)
		{
			return MFalse;
		}
		return MTrue;
	}
	MBool operator != (struct _tag_qvet_draw_pen_type &pen)
	{
		return !this->operator==(pen);
	}
	MDWord dwLineColor;//线条的颜色
	MDWord dwLineType;//0 实线 1 虚线
	MFloat fLineThickness;//线条的粗细程度, 相对于底图的百分比，例如底图宽度720， 真实的Thickness=720*fLineThickness
	MFloat fDottedLine;//相对于底图的百分比 例如底图宽度720， 真实的虚线的长度是=720*fDottedLine
	MBool  bEnableLight;//是否开启发光
	MFloat fLightRadius;//发光的宽度， 相对于底图的百分比 例如底图宽度720， 真实的发光半径是=720*fLightRadius
	MDWord dwLightColor;//发光的颜色
	MFloat fEdgeFeathering;//边缘羽化程度 0~1.0；相对于底图的百分比 例如底图宽度720， 真实的羽化的长度是=720*fEdgeFeathering
	MBool  bStatus;
}QVET_DRAW_PAINT_PEN_TYPE;



/***********************************SHAPE*****************************/
typedef struct _tag_qvet_draw_shape_base
{
	OVERLOAD_OPERATOR_NEW
	_tag_qvet_draw_shape_base()
	{
		euType = EU_DRAW_SHAPE_DEFAULT;
		dwGroupId = 0;
	}
	virtual ~_tag_qvet_draw_shape_base()
	{
	}
	virtual MBool operator ==(struct _tag_qvet_draw_shape_base *pShape) = 0;
	MDWord dwGroupId;
	EU_DRAW_SHAPE_TYPE euType;// 0 画笔，1.清屏  2套索， 3 涂料 
}QVET_DRAW_SHAPE_BASE_TYPE;

typedef struct _tag_qvet_draw_line_type :public QVET_DRAW_SHAPE_BASE_TYPE
{
	_tag_qvet_draw_line_type()
	{
		point_list.clear();
		euType = EU_DRAW_SHAPE_LINE;
	}
	~_tag_qvet_draw_line_type()
	{
		
	}
	_tag_qvet_draw_line_type(const struct _tag_qvet_draw_line_type& shape_type)
	{
		this->operator=(shape_type);
	}
	_tag_qvet_draw_line_type& operator=(const struct _tag_qvet_draw_line_type& line_type)
	{
		// 避免自赋值
		if (this != &line_type)
		{
			this->euType = line_type.euType;
			this->dwGroupId = line_type.dwGroupId;
			this->paint_type = line_type.paint_type;
			this->point_list.clear();
			this->point_list = line_type.point_list;
		}
		return *this;
	}
	MBool operator == (struct _tag_qvet_draw_shape_base *pShape)
	{
        _tag_qvet_draw_line_type *pLineShape = (_tag_qvet_draw_line_type *)pShape;
		MBool bPaintIsSame = MFalse;
		if (pLineShape == MNull)
			return MFalse;
		bPaintIsSame = (paint_type == pLineShape->paint_type);
		if (bPaintIsSame && point_list.size() == pLineShape->point_list.size())
			return MTrue;
		return MFalse;
	}

	QVET_DRAW_PAINT_PEN_TYPE paint_type;
	std::vector<MPOINT_FLOAT> point_list;//点的集合
}QVET_DRAW_SHAPE_LINE_TYPE;

typedef struct _tag_qvet_draw_erasure_type :public QVET_DRAW_SHAPE_BASE_TYPE
{
	_tag_qvet_draw_erasure_type()
	{

		euType = EU_DRAW_SHAPE_ERASURE;
	}
	~_tag_qvet_draw_erasure_type()
	{

	}
	MBool operator ==(struct _tag_qvet_draw_shape_base *pShape)
	{
      
		return MTrue;
	}
}QVET_DRAW_SHAPE_ERASURE_TYPE;

typedef struct _tag_qvet_draw_paint_type :public QVET_DRAW_SHAPE_BASE_TYPE
{
	_tag_qvet_draw_paint_type()
	{
		euType = EU_DRAW_SHAPE_PAINT;
	}
	~_tag_qvet_draw_paint_type()
	{

	}
	_tag_qvet_draw_paint_type(const struct _tag_qvet_draw_paint_type& shape_type)
	{
		this->operator=(shape_type);
	}

	_tag_qvet_draw_paint_type& operator=(const struct _tag_qvet_draw_paint_type& paint_type)
	{
		if (this != &paint_type) 
		{
			this->euType = paint_type.euType;
			this->dwGroupId = paint_type.dwGroupId;
			this->dwDrawColor = paint_type.dwDrawColor;
			this->point = paint_type.point;
		}
		return *this;
	}

	MBool operator ==(struct _tag_qvet_draw_shape_base* pShape)
	{
		_tag_qvet_draw_paint_type* pPaintShape = (_tag_qvet_draw_paint_type*)pShape;
		MBool bPaintIsSame = MFalse;
		if (pPaintShape == MNull)
			return MFalse;
		bPaintIsSame = (dwDrawColor == pPaintShape->dwDrawColor);
		if (bPaintIsSame && point.x == pPaintShape->point.x && point.y == pPaintShape->point.y)
			return MTrue;
		return MFalse;
	}
	MDWord dwDrawColor;//涂料颜色
	MPOINT_FLOAT point;
}QVET_DRAW_SHAPE_PAINT_TYPE;


typedef struct _tag_qvet_draw_shape_type
{
	OVERLOAD_OPERATOR_NEW
	_tag_qvet_draw_shape_type()
	{
		pType = nullptr;
	}
	_tag_qvet_draw_shape_type(MDWord dwType)
	{
		switch (dwType)
		{
		case EU_DRAW_SHAPE_LINE:
			pType = (QVET_DRAW_SHAPE_BASE_TYPE *)new QVET_DRAW_SHAPE_LINE_TYPE();
			break;
		case EU_DRAW_SHAPE_ERASURE:
			pType = (QVET_DRAW_SHAPE_BASE_TYPE *)new QVET_DRAW_SHAPE_ERASURE_TYPE();
			break;
		case EU_DRAW_SHAPE_PAINT:
			pType = (QVET_DRAW_SHAPE_BASE_TYPE*)new QVET_DRAW_SHAPE_PAINT_TYPE();
			break;
		}			
	}
	~_tag_qvet_draw_shape_type()
	{
		if (pType != nullptr)
		{
			delete pType;
			pType = nullptr;
		}
	}
	_tag_qvet_draw_shape_type(const struct _tag_qvet_draw_shape_type& shape_type)
	{
		this->operator=(shape_type);
	}

	_tag_qvet_draw_shape_type(_tag_qvet_draw_shape_type&& shape_type) noexcept
	{
		if (this != &shape_type)
		{
			pType = shape_type.pType;
			shape_type.pType = MNull;
		}
	}
	_tag_qvet_draw_shape_type& operator=(_tag_qvet_draw_shape_type&& shape_type) noexcept
	{
		if (this != &shape_type)
		{
			pType = shape_type.pType;
			shape_type.pType = MNull;
		}
		return *this;
	}
	
	_tag_qvet_draw_shape_type& operator=(const struct _tag_qvet_draw_shape_type& shape_type)
	{
		// 避免自赋值
		if (this != &shape_type)
		{
			if (shape_type.pType != MNull)
			{
				MDWord dwType = shape_type.pType->euType;
				switch (dwType)
				{
				case EU_DRAW_SHAPE_LINE:
					pType = (QVET_DRAW_SHAPE_BASE_TYPE *)new QVET_DRAW_SHAPE_LINE_TYPE();
					if (pType != MNull)
						*((QVET_DRAW_SHAPE_LINE_TYPE *)pType) = *((QVET_DRAW_SHAPE_LINE_TYPE *)shape_type.pType);
					break;
				case EU_DRAW_SHAPE_ERASURE:
					pType = (QVET_DRAW_SHAPE_BASE_TYPE *)new QVET_DRAW_SHAPE_ERASURE_TYPE();
					if (pType != MNull)
						*((QVET_DRAW_SHAPE_ERASURE_TYPE *)pType) = *((QVET_DRAW_SHAPE_ERASURE_TYPE *)shape_type.pType);
					break;
				case EU_DRAW_SHAPE_PAINT:
					pType = (QVET_DRAW_SHAPE_BASE_TYPE*)new QVET_DRAW_SHAPE_PAINT_TYPE();
					if (pType != MNull)
						*((QVET_DRAW_SHAPE_PAINT_TYPE*)pType) = *((QVET_DRAW_SHAPE_PAINT_TYPE*)shape_type.pType);
					break;
				}					
			}
			
		}
		return *this;
	}


	QVET_DRAW_SHAPE_BASE_TYPE *pType;
}QVET_DRAW_SHAPE_TYPE;
/***********************************END*****************************/


/***********************************Layer*****************************/
typedef struct _tag_qvet_layer_data
{
	OVERLOAD_OPERATOR_NEW
	_tag_qvet_layer_data()
	{
		bPaintStatus = MFalse;
		fAlpha = 1.0f;
		list.clear();
	}
	~_tag_qvet_layer_data()
	{

	}
	_tag_qvet_layer_data(_tag_qvet_layer_data&& layer_type) noexcept
	{
		this->operator=(layer_type);
	}
	_tag_qvet_layer_data& operator=(_tag_qvet_layer_data&& layer_type) noexcept
	{
		if (this != &layer_type)
		{
			bPaintStatus = layer_type.bPaintStatus;
			fAlpha = layer_type.fAlpha;
			list.clear();
			list.swap(layer_type.list);
		}
		return *this;
	}
	_tag_qvet_layer_data& operator=(const struct _tag_qvet_layer_data& layer_type)
	{
		// 避免自赋值
		if (this != &layer_type)
		{
			std::vector<QVET_DRAW_SHAPE_TYPE>::const_iterator itr = layer_type.list.begin();
			for (; itr != layer_type.list.end(); itr++)
			{
				QVET_DRAW_SHAPE_TYPE type;
				type.operator=(*itr);
				list.push_back(std::move(type));
			}
			bPaintStatus = layer_type.bPaintStatus;
			fAlpha = layer_type.fAlpha;
		}
		return *this;
	}
	MBool bPaintStatus;
	std::vector<QVET_DRAW_SHAPE_TYPE> list;
	MFloat fAlpha;
}QVET_DRAW_LAYER_DATA;

#endif
