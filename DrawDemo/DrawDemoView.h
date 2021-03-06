
// DrawDemoView.h: CDrawDemoView 类的接口
//

#pragma once

// 形状
#include "Element.h"
#include "ElementArray.h"
#include "EPoint.h"
#include "ELine.h"
#include "EPolyline.h"
#include "ERectangle.h"
#include "EPolygon.h"
#include "EEllipse.h"
#include "PenWidthDialog.h"

class CDrawDemoView : public CView
{
protected: // 仅从序列化创建
	CDrawDemoView();
	DECLARE_DYNCREATE(CDrawDemoView)

// 特性
public:
	CDrawDemoDoc* GetDocument() const;
	ElementArray editList;	// 编辑图形列表
	ElementArray clipboard;	// 剪贴板

// 变量
public:
	CRect clientRect;
	int clickCount;				// 左键点击次数

	/* 操作类别 */
	enum Operation {
		OPR_NONE,				// 无操作

		OPR_DRAW_POINT,			// 画点
		OPR_DRAW_LINE,			// 画线
		OPR_DRAW_POLYLINE,		// 画折线
		OPR_DRAW_RECTANGLE,		// 画矩形
		OPR_DRAW_POLYGON,		// 画多边形
		OPR_DRAW_ELLIPSE,		// 画椭圆

		OPR_EDIT_SELECT,		// 点选
		OPR_EDIT_SELECT_RANGE,	// 选取范围
		OPR_EDIT_MOVE,			// 移动
		OPR_EDIT_ZOOM,			// 缩放

		OPR_EDIT_ROTATE_CW,		// 顺时针旋转
		OPR_EDIT_ROTATE_CCW,	// 逆时针旋转
		OPR_EDIT_SYMMETRY_H,	// 水平对称
		OPR_EDIT_SYMMETRY_V,	// 水平对称


	};
	enum Operation oprType;		// 当前操作类别
	CPoint pointStart;			// 起始点
	CPoint pointLastMouse;		// 上一个鼠标点

	/* 颜色和笔宽 */
	COLORREF auxPenColor;		// 辅助线颜色
	int auxPenWidth;			// 辅助线宽
	COLORREF selectedColor;		// 已选图形颜色
	COLORREF penColor;			// 点和线颜色
	COLORREF fillColor;			// 填充颜色
	int lineWidth;				// 线宽;

// 操作
public:
	bool UpdateStatusBar(CString message, int position = 0);		// 更新状态栏消息
	void UpdateStatusBar(CPoint point, CString headMsg = _T(""));	// 在状态栏上显示坐标
	void ResetStatusBar(int position = 0);							// 重置状态栏消息如显示就绪
	void CancelOpr(bool isClearSelected = false);					// 取消操作
	bool CheckEditListNotEmpty();									// 检查是否选择图形并弹出提示

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CDrawDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
//	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	// 菜单消息
	// 文件
	afx_msg void OnFileSave();

	// 编辑
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditSelect();
	afx_msg void OnEditSelectRange();
	afx_msg void OnEditSelectAll();
	afx_msg void OnEditMove();
	afx_msg void OnEditZoom();
	afx_msg void OnEditDelete();
	// 旋转
	afx_msg void OnEditRotateCW();
	afx_msg void OnEditRotateCCW();
	afx_msg void OnEditSymmetryH();
	afx_msg void OnEditSymmetryV();
	// 更改
	afx_msg void OnEditChangeWidth();
	afx_msg void OnEditChangeColor();
	afx_msg void OnEditChangeFill();
	// 颜色
	afx_msg void OnEditSetColorAux();
	afx_msg void OnEditSetColorPen();
	afx_msg void OnEditSetColorFill();
	// 笔宽
	afx_msg void OnEditSetWidthPen();
	afx_msg void OnEditSetWidthAux();

	// 绘图
	afx_msg void OnDrawPoint();
	afx_msg void OnDrawLine();
	afx_msg void OnDrawPolyline();
	afx_msg void OnDrawRectangle();
	afx_msg void OnDrawPolygon();
	afx_msg void OnDrawEllipse();

	// 鼠标消息
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint point);

	// 其它消息
	afx_msg void OnCancelOpr();
	
};

#ifndef _DEBUG  // DrawDemoView.cpp 中的调试版本
inline CDrawDemoDoc* CDrawDemoView::GetDocument() const
   { return reinterpret_cast<CDrawDemoDoc*>(m_pDocument); }
#endif

