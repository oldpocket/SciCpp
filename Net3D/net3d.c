#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <time.h>
#define bool int
#define true 1
#define false 0
#define GLERROR                                                    \
    {                                                              \
        GLenum code = glGetError();                                \
        while (code!=GL_NO_ERROR)                                  \
        {                                                          \
            printf("%s\n",(char *) gluErrorString(code));          \
                code = glGetError();                               \
        }                                                          \
    }


static bool _mouseLeft   = false;
static bool _mouseMiddle = false;
static bool _mouseRight  = false;
int KeyDown[256];
static GLfloat light_ambient[]  = { 0.8, 0.8, 0.8, 1.0 };
static GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

static GLfloat mat_ambient[]    = { 1, 1, 1, 1 };
static GLfloat mat_diffuse[]    = { 0.9, 0.9, 0.9, 1.0 };
static GLfloat mat_specular[]   = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat high_shininess[] = { 100 };

static GLfloat mat_ambientlines[]    = { 1, 1, 1, 1.1 };
static GLfloat mat_diffuselines[]    = { 0.0, 0.0, 0.0, 0.0 };
static GLfloat mat_specularlines[]   = { 0, 0.0, 0.0, 0.0 };
static GLfloat high_shininesslines[] = { 100 };

GLfloat pov = 80.0;


char *readaline(FILE *inp, char *text, size_t size){
   size_t i = 0;
   for ( ;; ){
      int ch = fgetc(inp);
      if ( ch == '\n' || ch == EOF )
      {
         break;
      }
      if ( i < size - 1 )
      {
         text[i++] = ch;
      }
   }
   text[i] = '\0';
   return text;
}

bool compiledGL=false;
int compileCode=-1;
static int net3dPick(GLdouble x, GLdouble y,GLdouble delX, GLdouble delY);
static int compileGL();
static void decompileGL(int);
static void setHiers(int,int);
FILE *input_file;
FILE *names_file;
FILE *colors_file;
bool custom_colors=false;
bool custom_names=false;
int heigth=300;
int width=300;
float deltaz=10;
float nearclip=1;
float farclip=500;
int pause=0;
int centerize=0;
int iterations=1;
int showmindegree=0;
int showmaxdegree=50000;
float a=0.00001;
float b=0.1;
float beta=0.01;
float dt=1;
float tamanho=100;
int hierDeph=2;
////////////////

int nedges=0;
int nvertex=0;
char **nameslist;
float *Cc;
float *Rx; //posicao Rx
float *Ry; //posicao Ry
float *Rz; //posicao Rz
float *dRx; //posicao anterior Rx
float *dRy; //posicao anterior Ry
float *dRz; //posicao anterior Rz
float RMx=0;
float RMy=0;
float RMz=0;
int modes[10]={1,1,1,1,1,1,1,1,1,1};
int restaurar=false;
int **E;// arestas
int *Vin; //arestas
int *Vout; //arestas
int *Degree; //grau
float *Cr; //cor Rx
float *Cg; //cor Ry
float *Cb; //cor Rz
int *hiervertex;
int vselected=-1;
float maxdegree;
    GLfloat xspeed=0;
    GLfloat yspeed=0;
    GLfloat zspeed=0;
    GLfloat xpos=0;
    GLfloat ypos=0;
    GLfloat zpos=-30;
    
    int prevMouseX=0;
	int prevMouseY=0;
	
    int lastMouseX=0;
	int lastMouseY=0;
    int mouseRButtonDown = false;
    
    GLfloat scalespeed=0.05;
    
	GLfloat view_rotx = 0.0, view_roty = 0, view_rotz = 0;
	int gear1=0;
	
void rotateMouse(void){
	    xpos+=xspeed;
        ypos+=yspeed;
        zpos+=zspeed;
        
				
		glTranslatef(0,-0.0,-0.1);
        glTranslatef(0,0,+zpos);
        
        glRotatef(view_rotx, 1.0, 0.0, 0.0);
        glRotatef(view_roty, 0.0, 1.0, 0.0);
       // glRotatef(view_rotz, 0.0, 0.0, 1.0);
		
        glTranslatef(-xpos,0,ypos);
		
}/////////////////
//////
float rand_gen(){
	return rand() / (RAND_MAX + 1.0);
}
/////

///////
//PICK
static void (*selection)(void) = NULL;
static void (*pick)(GLint name) = NULL;

void net3dSelectionFunc(void (*f)(void))
{
    selection = f;
}

void net3dPickFunc(void (*f)(GLint name))
{
    pick = f;
}

/////
static void net3dReshape(int w,int h)
{
    glViewport(0,0,w,h);
	width=w;
	heigth=h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(pov,(double)w/(double)h,nearclip,farclip);
    glMatrixMode(GL_MODELVIEW);
}
/////////////////
void recenterPositions(){
	int i=0;
	float aRMx=0;
	float aRMy=0;
	float aRMz=0;
	for(i=0;i<nvertex;i++){
		aRMx+=Rx[i]/(float)nvertex;
		aRMy+=Ry[i]/(float)nvertex;
		aRMz+=Rz[i]/(float)nvertex;
	}
	
	 RMx=aRMx;
	 RMy=aRMy;
	 RMz=aRMz;
	//for(i=0;i<nvertex;i++){
	//	Rx[i]-=RMx/nvertex;
	//	Ry[i]-=RMy/nvertex;
	//	Rz[i]-=RMz/nvertex;
	//}
		
}//////
static void net3dMouse(int button, int state, int x, int y)
{
   GLint viewport[4];

   if (state==GLUT_DOWN){
		lastMouseX=x;
			lastMouseY=y;
      }
     
    if (state==GLUT_UP){
		if (abs(lastMouseX-x)<=4 &&abs(lastMouseY-y) <=4 ){
			net3dPick(x,glutGet(GLUT_WINDOW_HEIGHT)-1-y,3,3);
			if(compiledGL){
				decompileGL(compileCode);
				compiledGL=false;
			}
		}
			
			prevMouseX = x;
			prevMouseY = y;
        switch (button) {
            case GLUT_LEFT_BUTTON:   _mouseLeft   = false; break;
            case GLUT_MIDDLE_BUTTON: _mouseMiddle = false; break;
            case GLUT_RIGHT_BUTTON:  _mouseRight  = false; break;
        }
    }else{
			prevMouseX = x;
			prevMouseY = y;
        switch (button)
        {
            case GLUT_LEFT_BUTTON:   _mouseLeft   = true; break;
            case GLUT_MIDDLE_BUTTON: _mouseMiddle = true; break;
            case GLUT_RIGHT_BUTTON:  _mouseRight  = true; break;

        }
	}
    glGetIntegerv(GL_VIEWPORT,viewport);
	
    glutPostRedisplay();
}
////////////////
void net3dKeydDown(unsigned char key, int x, int y)
{
    KeyDown[key] = 1;
	//printf("mouseeh %c %d \n",key,KeyDown[key]);
        if(key=='a') zspeed=scalespeed;
        if(key=='s') zspeed=-scalespeed;
        if(key=='l') xspeed=scalespeed;
        if(key=='j') xspeed=-scalespeed;
        if(key=='i') yspeed=scalespeed;
        if(key=='k') yspeed=-scalespeed;}

void net3dKeyUp(unsigned char key, int x, int y)
{
    KeyDown[key] = 0;
	//printf("mouseeh %c %d \n",key,KeyDown[key]);
        if(key=='a') zspeed=0;
        if(key=='s') zspeed=-0;
        if(key=='l') xspeed=0;
        if(key=='j') xspeed=-0;
        if(key=='i') yspeed=0;
        if(key=='k') yspeed=-0;
		if(key=='p') pause = !pause;
		if(key=='e') {
			iterations++;
			printf("iterations:%d\n",iterations);
		}
		if(key=='w') {
			(iterations!=1)?iterations--:(iterations=1);
			printf("iterations:%d\n",iterations);
		}
		if(key=='m') {
			hierDeph++;
			printf("hierDeph:%d\n",hierDeph);
			memset( hiervertex, -1, nvertex*sizeof(int));
			setHiers(vselected,hierDeph);
			if(compiledGL){
				decompileGL(compileCode);
				compiledGL=false;
			}
		}
		if(key=='n') {
			(hierDeph!=1)?hierDeph--:(hierDeph=1);
			memset( hiervertex, -1, nvertex*sizeof(int));
			setHiers(vselected,hierDeph);
			printf("hierDeph:%d\n",hierDeph);
			if(compiledGL){
				decompileGL(compileCode);
				compiledGL=false;
			}
		}
	
		if(key=='c') centerize=!centerize;
		if(key=='[') {
			farclip=farclip*2;
			net3dReshape(width,heigth);
			printf("farclip:%f\n",farclip);
		}
		if(key==']') {
			farclip=farclip/2;
			net3dReshape(width,heigth);
			printf("farclip:%f\n",farclip);
		}
		if(key=='{') {
			nearclip=nearclip*2;
			net3dReshape(width,heigth);
			printf("farclip:%f\n",nearclip);
		}
		if(key=='}') {
			nearclip=nearclip/2;
			net3dReshape(width,heigth);
			printf("farclip:%f\n",nearclip);
		}
		if(key=='1') {
			modes[1]=!modes[1];
			printf("mode 1:%d\n",modes[1]);
			if(compiledGL){
				decompileGL(compileCode);
				compiledGL=false;
			}
		}
		if(key=='2') {
			modes[2]=!modes[2];
			printf("mode 2:%d\n",modes[2]);
			if(compiledGL){
				decompileGL(compileCode);
				compiledGL=false;
			}
		}
		if(key=='3') {
			modes[3]=!modes[3];
			printf("mode 3:%d\n",modes[3]);
			if(compiledGL){
				decompileGL(compileCode);
				compiledGL=false;
			}
		}
		if(key=='4') {
			modes[4]=!modes[4];
			printf("mode 4:%d\n",modes[4]);
			if(compiledGL){
				decompileGL(compileCode);
				compiledGL=false;
			}
		}
		if(key=='5') {
			modes[5]=!modes[5];
			printf("mode 5:%d\n",modes[5]);
			if(compiledGL){
				decompileGL(compileCode);
				compiledGL=false;
			}
		}
		if(key=='6') {
			modes[6]=!modes[6];
			printf("mode 6:%d\n",modes[6]);
			if(compiledGL){
				decompileGL(compileCode);
				compiledGL=false;
			}
		}
		if(key=='7') {
			modes[7]=!modes[7];
			printf("mode 7:%d\n",modes[7]);
			if(compiledGL){
				decompileGL(compileCode);
				compiledGL=false;
			}
		}
		if(key=='8') {
			modes[8]=!modes[8];
			printf("mode 8:%d\n",modes[8]);
			if(compiledGL){
				decompileGL(compileCode);
				compiledGL=false;
			}
		}
		if(key=='9') {
			modes[9]=!modes[9];
			printf("mode 9:%d\n",modes[9]);
			if(compiledGL){
				decompileGL(compileCode);
				compiledGL=false;
			}
		}
		if(key=='0') {
			if(modes[0]) glClearColor(0,0, 0, 1.0);
			else glClearColor(1.0,1.0, 1.0, 1.0);
			modes[0]=!modes[0];
			printf("mode 0:%d\n",modes[0]);
			
			if(compiledGL){
				decompileGL(compileCode);
				compiledGL=false;
			}
		}
		if(key=='r') {
			showmindegree--;
			if(compiledGL&&(modes[5]||modes[6])){
				decompileGL(compileCode);
				compiledGL=false;
			}
			printf("show min degree:%d\n",showmindegree);
		}
		if(key=='t') {
			showmindegree++;
			if(compiledGL&&(modes[5]||modes[6])){
				decompileGL(compileCode);
				compiledGL=false;
			}
			printf("show min degree:%d\n",showmindegree);
		}
		if(key=='y') {
			showmindegree=1;
			if(compiledGL&&(modes[5]||modes[6])){
				decompileGL(compileCode);
				compiledGL=false;
			}
			printf("show min degree:%d\n",showmindegree);
		}
		if(key=='f') {
			showmaxdegree--;
			if(compiledGL&&(modes[5]||modes[6])){
				decompileGL(compileCode);
				compiledGL=false;
			}
			printf("show max degree:%d\n",showmaxdegree);
		}
		if(key=='g') {
			showmaxdegree++;
			if(compiledGL&&(modes[5]||modes[6])){
				decompileGL(compileCode);
				compiledGL=false;
			}
			printf("show max degree:%d\n",showmaxdegree);
		}
		if(key=='h') {
			showmaxdegree=maxdegree;
			if(compiledGL&&(modes[5]||modes[6])){
				decompileGL(compileCode);
				compiledGL=false;
			}
			printf("show max degree:%d\n",showmaxdegree);
		}
}


/////////////////////////////////
static void net3dMotion(int x, int y)
{
    
	GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT,viewport);
    int dx=x-prevMouseX;
	int dy=y-prevMouseY;
	prevMouseX = x;
	prevMouseY = y;
    if (dx==0 && dy==0)
        return;
	
    if (_mouseMiddle || (_mouseLeft && _mouseRight)){
        
    } else
        if (_mouseLeft){
		    GLfloat thetaY = 360.0 * ( (float)(dx)/(float)width);
			GLfloat thetaX = 360.0 * ( (float)(dy)/(float)heigth);

		    view_rotx += thetaX;
			view_roty += thetaY;
			
			if(view_rotx>90) view_rotx=90;
			if(view_rotx<-90) view_rotx=-90;
			glutPostRedisplay();
		}
        else
            if (_mouseRight){
				zpos += deltaz *( 100.0*(float)(dx)/(float)width/(float)width*abs(x-0.5*width)+100.0*(float)(dy)/(float)heigth/(float)heigth*abs(y-0.5*heigth));
				if(zpos>0) zpos=0;
				glutPostRedisplay();
			}

}

////
void refreshPositions(){
	int i,j;
	float DX;
	float DY;
	float DZ;
	float DX2;
	float DY2;
	float DZ2;
	float D2;
	float dx;
	float dy;
	float dz;
	float Fx;
	float Fy;
	float Fz;
	float Ftotal;
	float w;
	for(i=0;i<nvertex;i++){
		
	}
	for(i=0;i<nvertex;i++){
			Fx=0;
			Fy=0;
			Fz=0;
		for(j=0;j<nvertex;j++){
			if(j!=i){
				DX=(Rx[i]-Rx[j]);
				DY=(Ry[i]-Ry[j]);
				DZ=(Rz[i]-Rz[j]);
				DX2=DX*DX;
				DY2=DY*DY;
				DZ2=DZ*DZ;
				D2=DX2+DY2+DZ2;
				dx=-DX/sqrt(D2);
				dy=-DY/sqrt(D2);
				dz=-DZ/sqrt(D2);
				w=(fmin(Degree[i],Degree[j]))/(float)maxdegree;
				Ftotal=-b/D2;
				if(E[i][j]>=1) Ftotal+=a*D2;
				Fx+=Ftotal*dx;
				Fy+=Ftotal*dy;
				Fz+=Ftotal*dz;
			}
		}
			Fx+=-beta*dRx[i];
			Fy+=-beta*dRy[i];
			Fz+=-beta*dRz[i];
			
			dRx[i]+=Fx*dt;
			dRy[i]+=Fy*dt;
			dRz[i]+=Fz*dt;
		
			Rx[i]+=dRx[i]*dt;
			Ry[i]+=dRy[i]*dt;
			Rz[i]+=dRz[i]*dt;
	}
	recenterPositions();
}
//////
void HSL2RGB(float *r, float *g, float *b, float h, float sl, float l) {
            float v;
		    *r = l;   // default to gray
            *g = l;
            *b = l;
			if(h>1) h=1;
            v = (l <= 0.5) ? (l * (1.0 + sl)) : (l + sl - l * sl);
            if (v > 0)
            {
                  float m;
                  float sv;
                  int sextant;
                  float fract, vsf, mid1, mid2;
 
                  m = l + l - v;
                  sv = (v - m ) / v;
                  h *= 6.0;
                  sextant = (int)h;
                  fract = h - sextant;
                  vsf = v * sv * fract;
                  mid1 = m + vsf;
                  mid2 = v - vsf;
				  
				  switch (sextant)
                  {
                        case 0:
                              *r = v;
                              *g = mid1;
                              *b = m;
                              break;
                        case 1:
                              *r = mid2;
                              *g = v;
                              *b = m;
                              break;
                        case 2:
                              *r = m;
                              *g = v;
                              *b = mid1;
                              break;
                        case 3:
                              *r = m;
                              *g = mid2;
                              *b = v;
                              break;
                        case 4:
                              *r = mid1;
                              *g = m;
                              *b = v;
                              break;
                        case 5:
                              *r = v;
                              *g = m;
                              *b = mid2;
                              break;
						case 6:
                              *r = v;
                              *g = mid1;
                              *b = m;
                              break;
                  }
            }
}

//////////
void HSVtoRGB( float *r, float *g, float *b, float h, float s, float v )
{
	int i;
	float f, p, q, t;
	if( s == 0 ) {
		// achromatic (grey)
		*r = *g = *b = v;
		return;
	}
	h /= 60;			// sector 0 to 5
	i = floor( h );
	f = h - i;			// factorial part of h
	p = v * ( 1 - s );
	q = v * ( 1 - s * f );
	t = v * ( 1 - s * ( 1 - f ) );
	switch( i ) {
		case 0:
			*r = v;
			*g = t;
			*b = p;
			break;
		case 1:
			*r = q;
			*g = v;
			*b = p;
			break;
		case 2:
			*r = p;
			*g = v;
			*b = t;
			break;
		case 3:
			*r = p;
			*g = q;
			*b = v;
			break;
		case 4:
			*r = t;
			*g = p;
			*b = v;
			break;
		default:		// case 5:
			*r = v;
			*g = p;
			*b = q;
			break;
	}
}
//////////////
void net3dIdle()
{
	int i;
	// Animation Code
 //if(KeyDown['a']==1) {printf("ok\n");};
	if(!pause) {
		for(i=0;i<iterations;i++)
			refreshPositions();
		if(compiledGL){
			decompileGL(compileCode);
			compiledGL=false;
		}
		
	}else if(!compiledGL){
		compileCode=compileGL();
		compiledGL=true;
	}
	glutPostRedisplay();
}//////
void setHiers(int sel, int level){
	int hl;
	int i,j;
	hiervertex[sel]=1;
	for(hl=1;hl<level;hl++){
		for(i=0;i<nvertex;i++){
			if(hiervertex[i]==hl){
				for(j=0;j<nvertex;j++){
					if(E[i][j]>=1) {
						if(hiervertex[j]==-1){
							hiervertex[j]=hl+1;
						}
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////
void net3dPickme(int min){
	vselected=-1;
	memset( hiervertex, -1, nvertex*sizeof(int));
	
	if (min>nvertex) return;
	vselected=min;
	
	if (vselected>=0){
		if(!custom_names) printf("Vértice selecionado: %d com grau %d .\n",vselected+1,Degree[min]);
		else printf("Vertex:%s (%d) degree: %d .\n",nameslist[min],vselected+1,Degree[min]);
		int i=0;
	
		printf("linked: ");
	
		setHiers(vselected,hierDeph);
		
		for(i=0;i<nvertex;i++){
			if(E[vselected][i]>=1) {
			if(!custom_names) printf("%d, ",i+1);
			else printf("%s(%d), ",nameslist[i],i+1);
		}
			
			;
		}
		printf("\n");
		printf("hier: ");
		for(i=0;i<nvertex;i++){
			if(hiervertex[i]>=0) printf("(%d,%d)",i,hiervertex[i]);
		}
		printf("\n---\n");
	}
	
}
///


///
void plotgraph(){
	int i=0;
	glPushMatrix();
		glTranslatef(-RMx,-RMy,-RMz);
		printf("Mx:%f My:%f Mz:%f\n",RMx,RMy,RMz);
		if(modes[1]){
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			
			for(i=0;i<nvertex;i++){
			if(modes[5]&&((Degree[i]<showmindegree)||(Degree[i]>showmaxdegree))) continue;
					
				glPushMatrix();
					glPushName(i);
					glTranslatef(Rx[i],Ry[i],Rz[i]);
					glColor4f(Cr[i],Cg[i],Cb[i],1);
					if(modes[3]) glutSolidSphere(0.7, 8, 8);
					else glutSolidCube(0.7);
					if (hiervertex[i]>0) {
						int hl=hiervertex[i];
						glColor4f(1,1,0.1, 0.2 +0.5*(1.0-(hl-1)/(float)(hierDeph)));
						if(modes[3]) glutSolidSphere(0.8, 20, 20);
						else glutSolidCube(0.8);
					}
					glPopName();
				glPopMatrix();
			}
		}
		if(modes[2]){
			glPushMatrix();
				glPushName(nvertex+1);
				float v1[]= {1,0.6,0.0,0.2};
				float v2[]= {1,0.6,0,0.2};
				float v3[]= {1,1,0,1};
				float v4[]= {1,1,0,1};
				glColor3f(0.5,0.5,0.3);
				glDisable(GL_LIGHTING);
				glDisable(GL_LIGHT0);
					for(i=0;i<nedges;i++){
					if(modes[6]&&((Degree[Vin[i]]<showmindegree)
						||(Degree[Vout[i]]<showmindegree)
						||(Degree[Vin[i]]>showmaxdegree)
						||(Degree[Vout[i]]>showmaxdegree))) continue;
					
					glPushMatrix();
						
						int hl1=hiervertex[Vin[i]];
						int hl2=hiervertex[Vout[i]];
						
						if(modes[4]){
							glEnable(GL_BLEND);
							glBlendFunc(GL_SRC_ALPHA, GL_ONE);
						}else{
							glDisable(GL_BLEND);
						}
						if((hl1==(hl2-1))||((hl1-1)==(hl2))){
							int hl=fmin(hl1,hl2);
							float w=(Degree[Vin[i]]+Degree[Vout[i]])/maxdegree/2.0;
								glLineWidth(fmax(1+4*(1.0-(hl-1)/(float)(hierDeph-1)),1));
							glColor4f(1,1,0,0.4);
							glBegin(GL_LINES);
								glColor4f(Cr[Vin[i]]*0.8+0.2,Cg[Vin[i]]*0.8+0.2,Cb[Vin[i]]*0.8,0.3+0.7*(1.0-(hl-1)/(float)(hierDeph-1)));
								glVertex3f(Rx[Vin[i]],Ry[Vin[i]],Rz[Vin[i]]);
								glColor4f(Cr[Vout[i]]*0.8+0.2,Cg[Vout[i]]*0.8+0.2,Cb[Vout[i]]*0.8,0.3+0.7*(1.0-(hl-1)/(float)(hierDeph-1)));
								glVertex3f(Rx[Vout[i]],Ry[Vout[i]],Rz[Vout[i]]);
							glEnd();
						}else{
							glColor4f(1,0.5,0,0.3);
							float w=(Degree[Vin[i]]+Degree[Vout[i]])/maxdegree/2.0;
							glLineWidth(2);
							glBegin(GL_LINES);
								glColor4f(Cr[Vin[i]]*0.8+0.2,Cg[Vin[i]]*0.8+0.2,Cb[Vin[i]]*0.8+0.2,w*0.4+0.2);
								glVertex3f(Rx[Vin[i]],Ry[Vin[i]],Rz[Vin[i]]);
								glColor4f(Cr[Vout[i]]*0.8+0.2,Cg[Vout[i]]*0.8+0.2,Cb[Vout[i]]*0.8+0.2,w*0.4+0.2);
								glVertex3f(Rx[Vout[i]],Ry[Vout[i]],Rz[Vout[i]]);
							glEnd();
						}
					glPopMatrix();
				
				}
				glPopName();
			glPopMatrix();
		}
	glPopMatrix();
}
////

void plototimized(){
	glPushMatrix();
		rotateMouse();
		if(compiledGL) glCallList(compileCode);
		else plotgraph();
	glPopMatrix();
}

int compileGL(){
	printf("Compiling\n");
	int compCode=glGenLists(1);
		glNewList(compCode, GL_COMPILE);
			plotgraph();
        glEndList();
	return compCode;
}
void decompileGL(int compCode){
		glDeleteLists(compCode,1);
		compiledGL=false;
}


void display(void)
{
   GLERROR;

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
   plototimized();
   glutSwapBuffers();
	
   GLERROR;
}

int main(int argc, char *argv[]){
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	srand( (unsigned)time( NULL ) );
	heigth=800;
	width=800;
    glutInitWindowSize(800,800);
    glutCreateWindow("Network 3D");
	
	int i=0;


	if(argc>1){
		if ((input_file = fopen(argv[1], "r")) == NULL){
			fprintf(stderr, "Nao pode abrir %s\n", argv[1]);
			return -1;
		}
	fscanf(input_file,"%d",&nvertex);
	fscanf(input_file,"%d",&nedges);
	Rx=(float*) calloc (nvertex+4,sizeof(float)); //posicao Rx
	Ry=(float*) calloc (nvertex+4,sizeof(float)); //posicao Ry
	Rz=(float*) calloc (nvertex+4,sizeof(float)); //posicao Rz
	dRx=(float*) calloc (nvertex+4,sizeof(float)); //posicao Rx
	dRy=(float*) calloc (nvertex+4,sizeof(float)); //posicao Ry
	dRz=(float*) calloc (nvertex+4,sizeof(float)); //posicao Rz
	Cr=(float*) calloc (nvertex+4,sizeof(float)); //cor Cr
	Cg=(float*) calloc (nvertex+4,sizeof(float)); //cor Cg
	Cb=(float*) calloc (nvertex+4,sizeof(float)); //cor Cb
	E=(int**) calloc (nvertex,sizeof(int*));
	Vin=(int*) calloc (nedges,sizeof(int));
	Vout=(int*) calloc (nedges,sizeof(int));
	Degree=(int*) calloc (nvertex,sizeof(int));
    hiervertex=(int*) calloc (nvertex,sizeof(int));;
	memset( hiervertex, 0, nvertex*sizeof(int));
	
	for (i=0;i<nvertex;i++){
		E[i]=(int*) calloc (nvertex,sizeof(int));
	}
	//dispoe aleatoriamente os nos no inicio
	for (i=0;i<nvertex;i++){
		Rx[i]=rand_gen()*tamanho-tamanho/2.0;
		Ry[i]=rand_gen()*tamanho-tamanho/2.0;
		Rz[i]=rand_gen()*tamanho-tamanho/2.0;
	}
	for (i=0;i<nedges;i++){
		int from=1;
		int to=1;
		fscanf(input_file,"%d",&from);
		fscanf(input_file,"%d",&to);
		//printf("from:%d to:%d\n",from,to);
		if(!E[from-1][to-1]) {
			E[from-1][to-1]++;
			Degree[to-1]++;
		}
		if(!E[to-1][from-1]) {
			E[to-1][from-1]++;
			Degree[from-1]++;
		}
		Vin[i]=from-1;
		Vout[i]=to-1;
	}
	
	maxdegree=0;
	for (i=0;i<nvertex;i++){
		if(maxdegree<Degree[i]) maxdegree=Degree[i];
	}
	showmaxdegree=maxdegree;
	//printf("Grau maximo:%f",maxdegree);
	for (i=0;i<nvertex;i++){
		float r=0;
		float g=0;
		float b=0;
		//HSVtoRGB(&r, &g, &b, (360*Degree[i]/maxdegree), 1,  0.8 );
		float v=1-(float)Degree[i]/(float)maxdegree;
		HSL2RGB(&r, &g, &b, pow(0.0001,1-v)*(240/360.0), 0.6, 0.4) ;
		Cr[i]=r;///maxdegree;
		Cg[i]=g;//1-v;//g;//rand_gen()*0.5+0.1;
		Cb[i]=b;//*v;//b;//rand_gen()*0.5+0.1;
		
	   // printf("Grau maximo:%f",Cr[i]);
	}
		fclose(input_file);
	}else {
	
		printf("float a=0.0001;\nfloat b=0.1;\nfloat beta=0.01;\nfloat dt=1;\nfloat tamanho=100;\n");
		return -1;
	
	}
	
	
	if(argc>2){
		if ((names_file = fopen(argv[2], "r")) == NULL){
			fprintf(stderr, "Nao pode abrir %s\n", argv[2]);
			return -1;
		}
			custom_names=true;
			nameslist=(char**) calloc (nvertex+4,sizeof(char*)); //posicao Rx
		for (i=0;i<nvertex;i++){
			nameslist[i]=(char*) calloc(100,sizeof(char));
			readaline(names_file,nameslist[i],100);
		}
		
		fclose(names_file);
	}
	
	
	recenterPositions();
	
	memset( KeyDown, 0, sizeof( KeyDown ) );
	glutDisplayFunc(display);
	glutReshapeFunc(net3dReshape);
	glutMouseFunc(net3dMouse);
    glutMotionFunc(net3dMotion);
    glutKeyboardFunc( net3dKeydDown );
    glutKeyboardUpFunc( net3dKeyUp );
	glutIdleFunc(net3dIdle);
	net3dSelectionFunc(plototimized);
	net3dPickFunc(net3dPickme);
	GLERROR;
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    //glShadeModel(GL_SMOOTH);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);//GL_ONE_MINUS_SRC_ALPHA);
	GLERROR;

    glViewport(0,0,width,heigth);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(pov,(double)500/(double)500,nearclip,farclip);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0,0, 0, 1.0);
    glClearDepth(1.0);
	//glEnable(GL_FOG);
	//glFogi(GL_FOG_MODE, GL_EXP2);;
	//glFogf(GL_FOG_DENSITY, 0.005f);
    //glEnable (GL_LINE_SMOOTH);
	//glEnable (GL_POLYGON_SMOOTH);
	//glHint (GL_LINE_SMOOTH_HINT, GL_FASTEST);	// Use The Good Calculations
	//glHint (GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
	//glHint (GL_POINT_SMOOTH_HINT, GL_FASTEST);
	
    glCullFace (GL_BACK);
    glEnable (GL_CULL_FACE);
    glutMainLoop();
}



static int net3dPick(GLdouble x, GLdouble y,GLdouble delX, GLdouble delY){
   GLuint buffer[1024*100];
   const int bufferSize =1024*100;

   GLint    viewport[4];
   GLdouble projection[16];

   GLint hits;
   GLint i,j,k;

   GLint  min  = -1;
   GLint  minreal  = -1;
   GLuint minZ = -1;

   glSelectBuffer(bufferSize,buffer);             
   glRenderMode(GL_SELECT);                        
   glInitNames();                                  

   glMatrixMode(GL_PROJECTION);
   glPushMatrix();                                 
   glGetIntegerv(GL_VIEWPORT,viewport);           
   glGetDoublev(GL_PROJECTION_MATRIX,projection);  
   glLoadIdentity();                               
   gluPickMatrix(x,y,delX,delY,viewport);          
   glMultMatrixd(projection);                      

   glMatrixMode(GL_MODELVIEW);

   if (selection)
      selection();                                 

   hits = glRenderMode(GL_RENDER);
   /*#ifndef NDEBUG
   if (hits!=0)
   {
      printf("hits = %d\n",hits);

      for (i=0,j=0; i<hits; i++)
      {
         printf("\tsize = %u, min = %u, max = %u : ",buffer[j],buffer[j+1],buffer[j+2]);
         for (k=0; k < (GLint) buffer[j]; k++)
            printf("%u ",buffer[j+3+k]);
         printf("\n");

         j += 3 + buffer[j];
      }
   }
   #endif*/

   if (hits)
   {
      for (i=0,j=0; i<hits; i++)
      {
         if (buffer[j+1]<minZ)
         {
            if (buffer[j]==0){
               min = -1;
            }else{
				min  = buffer[j+2+buffer[j]];
				if(min<nvertex){
					minreal=min;
				}
			}
			minZ = buffer[j+1];
         }

         j += buffer[j] + 3;
      }
   }

   glMatrixMode(GL_PROJECTION);
   glPopMatrix();                         /* Restore projection matrix           */
   glMatrixMode(GL_MODELVIEW);

   if (pick)
      pick(minreal);                          /* Pass pick event back to application */
	return minreal;
}

