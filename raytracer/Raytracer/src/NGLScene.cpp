#include "NGLScene.h"
#include <iostream>
#include <ngl/Vec3.h>
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <ngl/Vec3.h>
#include <QColorDialog>

#include "Scene.h"
#include "Sphere.h"

#include <nlohmann/json.hpp>

//----------------------------------------------------------------------------------------------------------------------
NGLScene::NGLScene( QWidget *_parent ) : QOpenGLWidget( _parent )
{

  // set this widget to have the initial keyboard focus
  setFocus();
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  this->resize(_parent->size());
    m_wireframe=false;
    m_rotation=0.0;
    m_scale=1.0;
    m_position=0.0;

    m_selectedObject=0;

    createMeshes();
}


void NGLScene::createMeshes(){
    std::ifstream i("scene.json");
    nlohmann::json j;
    i >> j;
    nlohmann::json::iterator it = j.begin();
    m_meshes.resize(j.size());

    //ngl::Random *rng = ngl::Random::instance();
    for(auto &m : m_meshes){
        m.pos=ngl::Vec3(it->at("x"), it->at("y"), it->at("z"));
        m.colour=ngl::Vec4(it->at("r"), it->at("g"), it->at("b"), 0.5f);
        //int type = static_cast<int>(rng->randomPositiveNumber(4));
        std::string oType = it->at("oType").dump(); //get as a string
        std::cout << oType <<std::endl;
        if(oType == "\"sphere\""){
            m.scale=ngl::Vec3(it->at("radius"), it->at("radius"), it->at("radius"));
            m.type=MeshType::SPHERE;
        }else if(oType == "\"obj\""){
            m.pos=ngl::Vec3(0.0f,0.0f,0.0f);
            m.scale=ngl::Vec3(1,1,1);
            m.type=MeshType::OBJ;
        }else if(oType == "\"abc\""){
            m.type=MeshType::TROLL;
        }else if(oType == "\"def\""){
            m.type=MeshType::CUBE;
        }

        it++;
    }
}


// This virtual function is called once before the first call to paintGL() or resizeGL(),
//and then once whenever the widget has been assigned a new QGLContext.
// This function should set up any required OpenGL context rendering flags, defining display lists, etc.
constexpr auto shaderProgram="PBR";
//----------------------------------------------------------------------------------------------------------------------
void NGLScene::initializeGL()
{

  ngl::NGLInit::instance();
  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  /// create our camera
  m_eye = (-0.4f,0.3f,2.2f);
  m_look = (0,0,-1.0f);
  ngl::Vec3 up(0,1,0);

  m_view=ngl::lookAt(m_eye,m_look,up);
  m_project=ngl::perspective(90,float(1024/720),0.1f,300.0f);
  // now to load the shader and set the values
  // grab an instance of shader manager
  ngl::ShaderLib* shader = ngl::ShaderLib::instance();
  // we are creating a shader called PBR to save typos
  // in the code create some constexpr
  constexpr auto vertexShader  = "PBRVertex";
  constexpr auto fragShader    = "PBRFragment";
  // create the shader program
  shader->createShaderProgram( shaderProgram );
  // now we are going to create empty shaders for Frag and Vert
  shader->attachShader( vertexShader, ngl::ShaderType::VERTEX );
  shader->attachShader( fragShader, ngl::ShaderType::FRAGMENT );
  // attach the source
  shader->loadShaderSource( vertexShader, "shaders/PBRVertex.glsl" );
  shader->loadShaderSource( fragShader, "shaders/PBRFragment.glsl" );
  // compile the shaders
  shader->compileShader( vertexShader );
  shader->compileShader( fragShader );
  // add them to the program
  shader->attachShaderToProgram( shaderProgram, vertexShader );
  shader->attachShaderToProgram( shaderProgram, fragShader );
  // now we have associated that data we can link the shader
  shader->linkProgramObject( shaderProgram );
  // and make it active ready to load values
  ( *shader )[ shaderProgram ]->use();
  shader->setUniform( "camPos", m_eye );
  // now a light
  // setup the default shader material and light porerties
  // these are "uniform" so will retain their values
  shader->setUniform("lightPosition",0.0, 2.0f, 2.0f );
  shader->setUniform("lightColor",400.0f,400.0f,400.0f);
  shader->setUniform("exposure",2.2f);
  shader->setUniform("albedo",0.950f, 0.71f, 0.29f);
  shader->setUniform("metallic",1.02f);
  shader->setUniform("roughness",0.38f);
  shader->setUniform("ao",0.2f);
  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
  prim->createSphere("sphere",1.0,40);
  m_text.reset(  new  ngl::Text(QFont("Arial",18)));
  m_text->setScreenSize(this->size().width(),this->size().height());
  m_text->setColour(1.0,1.0,0.0);

  //load obj
  m_mesh.reset( new ngl::Obj("box.obj"));
  m_mesh->createVAO();
  m_mesh->getFaceList();
  vertList = m_mesh->getVertexList();

  update();
}

//----------------------------------------------------------------------------------------------------------------------
//This virtual function is called whenever the widget has been resized.
// The new size is passed in width and height.
void NGLScene::resizeGL( int _w, int _h )
{
  m_project=ngl::perspective( 45.0f, static_cast<float>( _w ) / _h, 0.05f, 350.0f );
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
}


void NGLScene::loadMatricesToShader()
{
  ngl::ShaderLib* shader = ngl::ShaderLib::instance();
   shader->use("PBR");
   struct transform
   {
     ngl::Mat4 MVP;
     ngl::Mat4 normalMatrix;
     ngl::Mat4 M;
   };

    transform t;
    t.M=m_transform.getMatrix();

    t.MVP=m_project*m_view*t.M;
    t.normalMatrix=t.M;
    t.normalMatrix.inverse().transpose();
    shader->setUniformBuffer("TransformUBO",sizeof(transform),&t.MVP.m_00);
}

//----------------------------------------------------------------------------------------------------------------------
//This virtual function is called whenever the widget needs to be painted.
// this is our main drawing routine
void NGLScene::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_win.width,m_win.height);
  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
  if(m_wireframe == true)
  {
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  }
  else
  {
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  }

  ngl::Mat4 rotX;
  ngl::Mat4 rotY;
  ngl::Mat4 mouseRotation;
  rotX.rotateX(m_win.spinXFace);
  rotY.rotateY(m_win.spinYFace);
  mouseRotation=rotY*rotX;

    ngl::Transformation tx;

    //m_transform.setPosition(m_position);
    //m_transform.setScale(m_scale);
    //m_transform.setRotation(m_rotation);
    //loadMatricesToShader();
    //switch(m_selectedObject)
    //{
        //case 0 : prim->draw("teapot"); break;
        //case 1 : prim->draw("sphere"); break;
        //case 2 : prim->draw("cube"); break;
    //}

    std::cout << m_meshes.size() << std::endl;
    for(auto m : m_meshes){
        m_transform.setPosition(m.pos);
        tx.addRotation(m.rot);
        m_transform.setScale(m.scale);
        setColour(m.colour);
        loadMatricesToShader();
        //loadMatrixToLineShader(mouseRotation * tx.getMatrix());
        switch(m.type){
        case MeshType::OBJ : prim->draw("teapot"); break;
        case MeshType::CUBE : prim->draw("cube"); break;
        case MeshType::SPHERE : prim->draw("sphere"); break;
        case MeshType::TROLL : prim->draw("troll"); break;
        }
    }


    //m_text->renderText(10,10,"Ray tracer");
}

NGLScene::~NGLScene()
{
}

void NGLScene::toggleWireframe(bool _mode	 )
{
    m_wireframe=_mode;
    update();
}

void NGLScene::setXRotation( double _x		)
{
    //m_rotation.m_y=_y;
    update();
}

void NGLScene::setYRotation( double _y	)
{
    //m_rotation.m_y=_y;
    update();
}
void NGLScene::setZRotation( double _z )
{
    m_rotation.m_z=_z;
    update();
}

void NGLScene::setXScale( double _x	)
{
    m_scale.m_x=_x;
    update();
}

void NGLScene::setYScale(	 double _y)
{
    m_scale.m_y=_y;
    update();
}
void NGLScene::setZScale( double _z )
{
    m_scale.m_z=_z;
    update();
}

void NGLScene::setXPosition( double _x	)
{
    m_position.m_x=_x;
    update();
}

void NGLScene::setYPosition( double _y	)
{
    m_position.m_y=_y;
    update();
}
void NGLScene::setZPosition( double _z	 )
{
    m_position.m_z=_z;
    update();
}

void NGLScene::setObjectMode(	int _i)
{
    m_selectedObject=_i;
    update();
}
void NGLScene::setColour(ngl::Vec4 col)
{
    QColor colour = (col[0], col[1], col[2]);
    if( colour.isValid())
    {
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    (*shader)[shaderProgram]->use();
    shader->setUniform("albedo",static_cast<float>(col[0]),static_cast<float>(col[1]),static_cast<float>(col[2]));
    update();
    }
}

void NGLScene::renderScene()
{
    std::cout << "rendering!" << std::endl;
    Scene sc;
    sc.Render(m_samples, m_xRes, m_yRes);
}

void NGLScene::createSphere()
{
    Sphere s;

    std::cout << "creating sphere!" << std::endl;
    MeshData m;
        //m.pos=rng->getRandomPoint(40,0,40);
        m.rot.m_y=0;
        m.scale.set(1.0f,1.0f,1.0f);
        //m.colour=rng->getRandomColour4();
        m.type=MeshType::SPHERE;
        m_meshes.push_back(m);
}

void NGLScene::setSamples(int _s)
{
    m_samples = _s;
}

void NGLScene::setXRes(int _x)
{
    m_xRes = _x;
}

void NGLScene::setYRes(int _y)
{
    m_yRes = _y;
}


//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseMoveEvent( QMouseEvent* _event )
{
  // note the method buttons() is the button state when event was called
  // that is different from button() which is used to check which button was
  // pressed when the mousePress/Release event is generated
  if ( m_win.rotate && _event->buttons() == Qt::LeftButton )
  {
    int diffx = _event->x() - m_win.origX;
    int diffy = _event->y() - m_win.origY;
    //m_win.spinXFace += static_cast<int>( 0.5f * diffy );
    //m_win.spinYFace += static_cast<int>( 0.5f * diffx );
    m_win.origX = _event->x();
    m_win.origY = _event->y();
    m_rotation.m_y += static_cast<int>( 0.5f * diffx );
    //m_rotation.m_x += static_cast<int>( 0.5f * diffy );

    update();
  }
  // right mouse translate code
  else if ( m_win.translate && _event->buttons() == Qt::RightButton )
  {
    int diffX      = static_cast<int>( _event->x() - m_win.origXPos );
    int diffY      = static_cast<int>( _event->y() - m_win.origYPos );
    m_win.origX += diffX;
    m_win.origY += diffY;
    m_modelPos.m_x += INCREMENT * diffX;
    m_modelPos.m_y -= INCREMENT * diffY;
    update();
  }
}


//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mousePressEvent( QMouseEvent* _event )
{
  // that method is called when the mouse button is pressed in this case we
  // store the value where the maouse was clicked (x,y) and set the Rotate flag to true
  if ( _event->button() == Qt::LeftButton )
  {
    m_win.origX  = _event->x();
    m_win.origY  = _event->y();
    m_win.rotate = true;
  }
  // right mouse translate mode
  else if ( _event->button() == Qt::RightButton )
  {
    m_win.origXPos  = _event->x();
    m_win.origYPos  = _event->y();
    m_win.translate = true;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseReleaseEvent( QMouseEvent* _event )
{
  // that event is called when the mouse button is released
  // we then set Rotate to false
  if ( _event->button() == Qt::LeftButton )
  {
    m_win.rotate = false;
  }
  // right mouse translate mode
  if ( _event->button() == Qt::RightButton )
  {
    m_win.translate = false;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::wheelEvent( QWheelEvent* _event )
{

    //ngl::Vec3 eye(0.0f,2.0f,2.0f);
    //ngl::Vec3 look(0,0,0);
    ngl::Vec3 up(0,1,0);


  // check the diff of the wheel position (0 means no change)
  if ( _event->delta() > 0 )
  {
    m_eye += ZOOM*(m_look - m_eye);
  }
  else if ( _event->delta() < 0 )
  {
    m_eye += -ZOOM*(m_look - m_eye);
  }
  m_view=ngl::lookAt(m_eye,m_look,up);
  m_project=ngl::perspective(90,float(1024/720),0.1f,300.0f);

  update();
}
