
#include "OpenCVSkelton.h"



//=======================================================================================
/*
	エフェクトコントロールで表示されるUIパーツの登録
	Param_Utils.hを参照のこと
*/
static PF_Err
ParamsSetup(
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output)
{
	PF_Err			err = PF_Err_NONE;
	PF_ParamDef		def;


	//----------------------------------------------------------------
	//位置の指定
	AEFX_CLR_STRUCT(def);
	PF_ADD_POINT(STR_STR_POS,			/*"New Center"*/
		50,	// X
		50,	// Y
		0,	// Flag
		ID_STR_POS
	);
	//----------------------------------------------------------------
	//色の指定
	AEFX_CLR_STRUCT(def);
	//def.flags = PF_ParamFlag_CANNOT_TIME_VARY;//これをつけるとキーフレームが撃てなくなる
	//def.flags = PF_ParamFlag_CANNOT_INTERP;	//キーフレームの自動保管を停止する
	PF_ADD_COLOR(STR_STR_COL,
		0xFF, 
		0xFF,
		0x00,
		ID_STR_COLOR
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_FLOAT_SLIDER(STR_STR_SIZE,	//Name
		0,							//VALID_MIN
		10,						//VALID_MAX
		0,							//SLIDER_MIN
		10,						//SLIDER_MAX
		1,							//CURVE_TOLERANCE
		1.5,						//DFLT
		1,							//PREC
		0,							//DISP
		0,							//WANT_PHASE
		ID_STR_SIZE
	);

	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_FLOAT_SLIDER(STR_R,	//Name
		-100,							//VALID_MIN
		100,						//VALID_MAX
		-100,							//SLIDER_MIN
		100,						//SLIDER_MAX
		1,							//CURVE_TOLERANCE
		0,							//DFLT
		1,							//PREC
		0,							//DISP
		0,							//WANT_PHASE
		ID_R
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_FLOAT_SLIDER(STR_G,	//Name
		-100,							//VALID_MIN
		100,						//VALID_MAX
		-100,							//SLIDER_MIN
		100,						//SLIDER_MAX
		1,							//CURVE_TOLERANCE
		0,							//DFLT
		1,							//PREC
		0,							//DISP
		0,							//WANT_PHASE
		ID_G
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_FLOAT_SLIDER(STR_B,	//Name
		-100,							//VALID_MIN
		100,						//VALID_MAX
		-100,							//SLIDER_MIN
		100,						//SLIDER_MAX
		1,							//CURVE_TOLERANCE
		0,							//DFLT
		1,							//PREC
		0,							//DISP
		0,							//WANT_PHASE
		ID_B
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	//def.flags = PF_ParamFlag_START_COLLAPSED;
	PF_ADD_TOPIC(STR_TOPIC, ID_TOPIC);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	//def.ui_flags = PF_PUI_DISABLED;
	PF_ADD_SLIDER(STR_ADD_SLIDER,	//パラメータの名前
		-30000, 		//数値入力する場合の最小値
		30000,			//数値入力する場合の最大値
		0,				//スライダーの最小値 
		100,			//スライダーの最大値
		0,				//デフォルトの値
		ID_ADD_SLIDER
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	//def.flags = PF_ParamFlag_CANNOT_TIME_VARY;//これをつけるとキーフレームが撃てなくなる
	PF_ADD_FIXED(STR_FIXED_SLIDER,	//パラメータの名前
		0, 				//数値入力する場合の最小値
		100,			//数値入力する場合の最大値
		0,				//スライダーの最小値 
		100,			//スライダーの最大値
		100,			//デフォルトの値
		1,				//数値表示に関するフラグ 
		0,
		0,
		ID_FIXED_SLIDER
	);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_FLOAT_SLIDER(STR_FLOAT_SLIDER,	//Name
		-10000,							//VALID_MIN
		10000,						//VALID_MAX
		0,							//SLIDER_MIN
		1000,						//SLIDER_MAX
		1,							//CURVE_TOLERANCE
		500,						//DFLT
		1,							//PREC
		0,							//DISP
		0,							//WANT_PHASE
		ID_FLOAT_SLIDER
	);
//----------------------------------------------------------------
//色の指定
AEFX_CLR_STRUCT(def);
//def.flags = PF_ParamFlag_CANNOT_TIME_VARY;//これをつけるとキーフレームが撃てなくなる
PF_ADD_COLOR(STR_COLOR,
	0xFF,
	0xFF,
	0xFF,
	ID_COLOR
);
//----------------------------------------------------------------
AEFX_CLR_STRUCT(def);
//def.flags = PF_ParamFlag_SUPERVISE |
//	PF_ParamFlag_CANNOT_TIME_VARY |
//	PF_ParamFlag_CANNOT_INTERP;
PF_ADD_CHECKBOX(STR_CHECKBOX1,
	STR_CHECKBOX2,
	TRUE,
	0,
	ID_CHECKBOX
);
//----------------------------------------------------------------
//角度
AEFX_CLR_STRUCT(def);
PF_ADD_ANGLE(STR_ANGLE, 0, ID_ANGLE);
//----------------------------------------------------------------
//ポップアップメニュー
AEFX_CLR_STRUCT(def);
PF_ADD_POPUP(STR_POPUP,
	STR_POPUP_COUNT,	//メニューの数
	STR_POPUP_DFLT,	//デフォルト
	STR_POPUP_ITEMS,
	ID_POPUP
);
//----------------------------------------------------------------
//位置の指定
AEFX_CLR_STRUCT(def);
PF_ADD_POINT(STR_POINT,			/*"New Center"*/
	50,	// X
	50,	// Y
	0,	// Flag
	ID_POINT
);
//----------------------------------------------------------------
AEFX_CLR_STRUCT(def);
PF_END_TOPIC(ID_TOPIC_END);

out_data->num_params = ID_NUM_PARAMS;

return err;
}

//=======================================================================================
/*
static PF_Err
FilterImage8 (
	void		*refcon,
	A_long		xL,
	A_long		yL,
	PF_Pixel8	*inP,
	PF_Pixel8	*outP)
{
	PF_Err			err = PF_Err_NONE;

	NoiseInfo *	niP		= reinterpret_cast<NoiseInfo*>(refcon);
	PF_FpLong	tempF		= 0;

	if (niP){
		tempF 	= rand() % PF_MAX_CHAN8;
		tempF	*= (niP->valF / SLIDER_MAX);

		outP->alpha		=	inP->alpha;
		outP->red		=	MIN(PF_MAX_CHAN8, inP->red + (A_u_char) tempF);
		outP->green		=	MIN(PF_MAX_CHAN8, inP->green + (A_u_char) tempF);
		outP->blue		=	MIN(PF_MAX_CHAN8, inP->blue + (A_u_char) tempF);
	}
	return err;
}
*/
//-------------------------------------------------------------------------------------------------
static PF_Err
PixelFunc8(
	void		*refcon,
	A_long		xL,
	A_long		yL,
	CV8UC4_Pixel	*inP,
	CV8UC4_Pixel	*outP)
{
	PF_Err			err = PF_Err_NONE;

	ParamInfo *	infoP = reinterpret_cast<ParamInfo*>(refcon);


	A_u_char *inP2;
	inP2 = (A_u_char *)inP;
	A_u_char *outP2;
	outP2 = (A_u_char *)inP;


	//blue grren redの順
	for (int i = 0; i < 3; i++)
	{
		if (infoP->bgr[i] == 0)
		{
			outP2[i] = inP2[i];
		}
		else if (infoP->bgr[i] < 0)
		{
			outP2[i] = RoundByteFpLong((double)inP2[i] + ((double)inP2[i] * infoP->bgr[i]));
		}
		else if (infoP->bgr[i] > 0)
		{
			outP2[i] = RoundByteFpLong(inP2[i] + (PF_MAX_CHAN8 - inP2[i])*(infoP->bgr[i] ));
		}
	}
	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err
PixelFunc16(
	void		*refcon,
	A_long		xL,
	A_long		yL,
	CV16UC4_Pixel	*inP,
	CV16UC4_Pixel	*outP)
{
	PF_Err			err = PF_Err_NONE;

	ParamInfo *	infoP = reinterpret_cast<ParamInfo*>(refcon);

	A_u_short *inP2;
	inP2 = (A_u_short *)inP;
	A_u_short *outP2;
	outP2 = (A_u_short *)inP;

	//blue grren redの順
	for (int i = 0; i < 3; i++)
	{
		if (infoP->bgr[i] == 0)
		{
			outP2[i] = inP2[i];
		}
		else if (infoP->bgr[i] < 0)
		{
			outP2[i] = RoundShortFpLong((double)inP2[i] + ((double)inP2[i] * infoP->bgr[i]));
		}
		else if (infoP->bgr[i] > 0)
		{
			outP2[i] = RoundShortFpLong(inP2[i] + (PF_MAX_CHAN16 - inP2[i])*(infoP->bgr[i]));
		}
	}
	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err
PixelFunc32(
	void		*refcon,
	A_long		xL,
	A_long		yL,
	CV32UC4_Pixel	*inP,
	CV32UC4_Pixel	*outP)
{
	PF_Err			err = PF_Err_NONE;

	ParamInfo *	infoP = reinterpret_cast<ParamInfo*>(refcon);

	PF_FpShort *inP2;
	inP2 = (PF_FpShort *)inP;
	PF_FpShort *outP2;
	outP2 = (PF_FpShort *)inP;


	//blue grren redの順
	for (int i = 0; i < 3; i++)
	{
		if (infoP->bgr[i] == 0)
		{
			outP2[i] = inP2[i];
		}
		else if (infoP->bgr[i] < 0)
		{
			outP2[i] = RoundFpShortDouble((double)inP2[i] + ((double)inP2[i] * infoP->bgr[i]));
		}
		else if (infoP->bgr[i] > 0)
		{
			double v = inP2[i];
			if (v > 1) v = 1;
			outP2[i] = RoundFpShortDouble(inP2[i] + (1 - v)*(infoP->bgr[i]));
		}
	}
	return err;
}
//-------------------------------------------------------------------------------------------------
PF_Err TestPixelFunc8(CAE *ae, ParamInfo *infoP)
{
	PF_Err			err = PF_Err_NONE;

	cv::Mat src = CAEcv::WorldToMat8(ae->output);


	ERR(CAEcv::iterate8((refconType)infoP,src,src, PixelFunc8));

	CAEcv::Mat2World8(src, ae->output);


	return err;
}
//-------------------------------------------------------------------------------------------------
PF_Err TestPixelFunc16(CAE *ae, ParamInfo *infoP)
{
	PF_Err			err = PF_Err_NONE;

	cv::Mat src = CAEcv::WorldToMat16(ae->output);

	ERR(CAEcv::iterate16((refconType)infoP, src, src, PixelFunc16));

	CAEcv::Mat2World16(src, ae->output);


	return err;
}
//-------------------------------------------------------------------------------------------------
PF_Err TestPixelFunc32(CAE *ae, ParamInfo *infoP)
{
	PF_Err			err = PF_Err_NONE;

	cv::Mat src = CAEcv::WorldToMat32(ae->output);

	ERR(CAEcv::iterate32((refconType)infoP, src, src, PixelFunc32));

	CAEcv::Mat2World32(src, ae->output);


	return err;
}
//-------------------------------------------------------------------------------------------------
PF_Err Test8(CAE *ae, ParamInfo *infoP)
{
	PF_Err			err = PF_Err_NONE;

	cv::Mat src = CAEcv::WorldToMat8(ae->input);

	cv::Point pnt(infoP->str_point.x >> 16, infoP->str_point.y >> 16);

	cv::Scalar p = CAEcv::PF_PixelTo(infoP->str_color);
	cv::putText(src, "After Effects", pnt ,cv::FONT_HERSHEY_TRIPLEX, infoP->str_size,p , (int)(2 * infoP->str_size), CV_AA);

	CAEcv::Mat2World8(src,ae->output);


	return err;
}
//-------------------------------------------------------------------------------------------------
PF_Err Test16(CAE *ae, ParamInfo *infoP)
{
	PF_Err			err = PF_Err_NONE;

	cv::Mat src = CAEcv::WorldToMat16(ae->input);

	cv::Point pnt(infoP->str_point.x >> 16, infoP->str_point.y >> 16);
	cv::Scalar p = CAEcv::PF_PixelTo(PIXEL_CONV8TO16(infoP->str_color));

	cv::putText(src, "After Effects", pnt, cv::FONT_HERSHEY_TRIPLEX, infoP->str_size, p, (int)(2*infoP->str_size), CV_AA);

	CAEcv::Mat2World16(src, ae->output);


	return err;
}
//-------------------------------------------------------------------------------------------------
PF_Err Test32(CAE *ae, ParamInfo *infoP)
{
	PF_Err			err = PF_Err_NONE;

	cv::Mat src = CAEcv::WorldToMat32(ae->input);

	cv::Point pnt(infoP->str_point.x >> 16, infoP->str_point.y >> 16);
	cv::Scalar p = CAEcv::PF_PixelTo(PIXEL_CONV8TO32(infoP->str_color));

	cv::putText(src, "After Effects", pnt, cv::FONT_HERSHEY_TRIPLEX, infoP->str_size, p, (int)(2 * infoP->str_size), CV_AA);

	CAEcv::Mat2World16(src, ae->output);


	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err GetParams(CAE *ae, ParamInfo *infoP)
{
	PF_Err		err = PF_Err_NONE;

	ERR(ae->GetFIXEDPOINT(ID_STR_POS, &infoP->str_point));
	ERR(ae->GetCOLOR(ID_STR_COLOR, &infoP->str_color));
	ERR(ae->GetFLOAT(ID_STR_SIZE, &infoP->str_size));

	PF_FpLong d;
	ERR(ae->GetFLOAT(ID_B, &d));
	infoP->bgr[0] = d/100;
	ERR(ae->GetFLOAT(ID_G, &d));
	infoP->bgr[1] = d/100;
	ERR(ae->GetFLOAT(ID_R, &d));
	infoP->bgr[2] = d/100;

	ERR(ae->GetADD(ID_ADD_SLIDER, &infoP->add));
	ERR(ae->GetFIXED(ID_FIXED_SLIDER, &infoP->fxd));
	ERR(ae->GetFLOAT(ID_FLOAT_SLIDER, &infoP->flt));
	ERR(ae->GetCOLOR(ID_COLOR, &infoP->color));
	ERR(ae->GetCHECKBOX(ID_CHECKBOX, &infoP->checkbox));
	ERR(ae->GetANGLE(ID_ANGLE, &infoP->angle));
	ERR(ae->GetPOPUP(ID_POPUP, &infoP->popup));
	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err
Exec(CAE *ae, ParamInfo *infoP)
{
	PF_Err	err = PF_Err_NONE;

	//画面をコピー
	//ERR(ae->CopyInToOut());


	switch (ae->pixelFormat())
	{
	case PF_PixelFormat_ARGB128:
		//ERR(ae->iterate32((refconType)infoP,FilterImage32));
		ERR(Test32(ae, infoP));
		TestPixelFunc32(ae, infoP);
		break;
	case PF_PixelFormat_ARGB64:
		//ERR(ae->iterate16((refconType)infoP,FilterImage16));
		ERR(Test16(ae, infoP));
		TestPixelFunc16(ae, infoP);
		break;
	case PF_PixelFormat_ARGB32:
		ERR(Test8(ae, infoP));
		TestPixelFunc8(ae, infoP);
		break;
	}
	return err;
}


//=======================================================================================
#include "OpenCVSkelton_Entry.h"
