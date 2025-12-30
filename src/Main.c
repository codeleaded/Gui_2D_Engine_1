#if defined __linux__
#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/AffineTransform.h"
#elif defined _WINE
#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#elif defined _WIN32
#include "F:/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#elif defined(__APPLE__)
#error "Apple not supported!"
#else
#error "Platform not supported!"
#endif


Vector lines;
Vec2 cam;
float a;

void CreateCube(Vector* v,Vec2 p,Vec2 d){
	Vector_Push(&lines,(Line[]){ Line_New((Vec2){ p.x,p.y },(Vec2){ p.x + d.x,p.y }) });
	Vector_Push(&lines,(Line[]){ Line_New((Vec2){ p.x,p.y },(Vec2){ p.x,p.y + d.y }) });
	Vector_Push(&lines,(Line[]){ Line_New((Vec2){ p.x + d.x,p.y },(Vec2){ p.x + d.x,p.y + d.y }) });
	Vector_Push(&lines,(Line[]){ Line_New((Vec2){ p.x,p.y + d.y },(Vec2){ p.x + d.x,p.y + d.y }) });
}

void Setup(AlxWindow* w){
	cam = (Vec2){ 0.0f,0.0f };
	a = 0.0f;

	lines = Vector_New(sizeof(Line));
	CreateCube(&lines,(Vec2){ -3.0f,1.0f },(Vec2){ 1.0f,1.0f });
	CreateCube(&lines,(Vec2){ -1.0f,1.0f },(Vec2){ 1.0f,1.0f });
	CreateCube(&lines,(Vec2){ 1.0f,1.0f },(Vec2){ 1.0f,1.0f });
	CreateCube(&lines,(Vec2){ 3.0f,1.0f },(Vec2){ 1.0f,1.0f });
}

void Update(AlxWindow* w){
	const Vec2 front = Vec2_Mulf(Vec2_OfAngle(a - 2 * F32_PI025),1.0f * w->ElapsedTime);

	if(Stroke(ALX_KEY_W).DOWN) cam = Vec2_Add(cam,front);
	if(Stroke(ALX_KEY_S).DOWN) cam = Vec2_Sub(cam,front);
	if(Stroke(ALX_KEY_A).DOWN) cam = Vec2_Add(cam,Vec2_Perp(front));
	if(Stroke(ALX_KEY_D).DOWN) cam = Vec2_Sub(cam,Vec2_Perp(front));

	if(Stroke(ALX_KEY_LEFT).DOWN) a += F32_PI * w->ElapsedTime;
	if(Stroke(ALX_KEY_RIGHT).DOWN) a -= F32_PI * w->ElapsedTime;

	Clear(BLACK);
	
	AffineTransform at = AffineTransform_New();
	AffineTransform_Trans(&at,cam);
	AffineTransform_RotateZ(&at,a);

	for (int i = 0;i<lines.size;i++){
		Line* l = (Line*)Vector_Get(&lines,i);
		
		const Line trans = Line_New(AffineTransform_Calc(&at,l->s),AffineTransform_Calc(&at,l->e));
		
		Line proj = trans;
		proj.s.x /= proj.s.y;
		proj.e.x /= proj.e.y;

		if(proj.s.y < 0.0f || proj.e.y < 0.0f) continue;
		
		const float sx = (proj.s.x + 1.0f) * GetWidth() / 2;
		const float ex = (proj.e.x + 1.0f) * GetWidth() / 2;

		const float m = GetHeight() / 2;
		const float sy = (GetHeight() / 2) / proj.s.y;
		const float ey = (GetHeight() / 2) / proj.e.y;

		//Line_RenderX(WINDOW_STD_ARGS,(Vec2){ sx,GetHeight() / 2 },(Vec2){ ex,GetHeight() / 2 },WHITE,1.0f);

		//Triangle_RenderX(
		//	WINDOW_STD_ARGS,
		//	(Vec2){ sx,m - sy },
		//	(Vec2){ sx,m + sy },
		//	(Vec2){ ex,m + ey },
		//	WHITE
		//);
		//Triangle_RenderX(
		//	WINDOW_STD_ARGS,
		//	(Vec2){ sx,m - sy },
		//	(Vec2){ ex,m + ey },
		//	(Vec2){ ex,m - ey },
		//	WHITE
		//);

		Triangle_RenderXWire(
			WINDOW_STD_ARGS,
			(Vec2){ sx,m - sy },
			(Vec2){ sx,m + sy },
			(Vec2){ ex,m + ey },
			WHITE,1.0f
		);
		Triangle_RenderXWire(
			WINDOW_STD_ARGS,
			(Vec2){ sx,m - sy },
			(Vec2){ ex,m + ey },
			(Vec2){ ex,m - ey },
			WHITE,1.0f
		);

		//RenderTriangleWire(
		//	((Vec2){ triProjected.p[0].x,triProjected.p[0].y }),
		//	((Vec2){ triProjected.p[1].x,triProjected.p[1].y }),
		//	((Vec2){ triProjected.p[2].x,triProjected.p[2].y }),
		//	WHITE,1.0f
		//);
	}
}

void Delete(AlxWindow* w){
	Vector_Free(&lines);
}

int main(){
    if(Create("2D Engine",2500,1200,1,1,Setup,Update,Delete))
        Start();
    return 0;
}