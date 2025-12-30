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

void Setup(AlxWindow* w){
	cam = (Vec2){ 0.0f,0.0f };
	a = 0.0f;

	lines = Vector_New(sizeof(Line));
	Vector_Push(&lines,(Line[]){ Line_New((Vec2){ -0.5f,1.0f },(Vec2){ 0.5f,1.0f }) });
	Vector_Push(&lines,(Line[]){ Line_New((Vec2){ -0.5f,1.0f },(Vec2){ -0.5f,1.5f }) });
	Vector_Push(&lines,(Line[]){ Line_New((Vec2){ 0.5f,1.0f },(Vec2){ 0.5f,1.5f }) });
}

void Update(AlxWindow* w){
	const Vec2 front = Vec2_Mulf(Vec2_OfAngle(a),1.0f * w->ElapsedTime);

	if(Stroke(ALX_KEY_W).PRESSED) cam = Vec2_Add(cam,front);
	if(Stroke(ALX_KEY_S).PRESSED) cam = Vec2_Sub(cam,front);
	if(Stroke(ALX_KEY_A).PRESSED) a -= F32_PI * w->ElapsedTime;
	if(Stroke(ALX_KEY_D).PRESSED) a += F32_PI * w->ElapsedTime;

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
		
		const float sx = proj.s.x * GetWidth() / 2;
		const float ex = proj.e.x * GetWidth() / 2;

		Line_RenderX(WINDOW_STD_ARGS,(Vec2){ sx,GetHeight() / 2 },(Vec2){ ex,GetHeight() / 2 },WHITE,1.0f);


		//RenderTriangleWire(
		//	((Vec2){ triProjected.p[0].x,triProjected.p[0].y }),
		//	((Vec2){ triProjected.p[1].x,triProjected.p[1].y }),
		//	((Vec2){ triProjected.p[2].x,triProjected.p[2].y }),
		//	WHITE,1.0f
		//);
	}
}

void Delete(AlxWindow* w){
	Vector_Free(&meshCube.tris);
}

int main(){
    if(Create("3D Test Tex",2500,1200,1,1,Setup,Update,Delete))
        Start();
    return 0;
}