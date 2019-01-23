#ifndef NGLSCENE_H_
#define NGLSCENE_H_

#include <ngl/Transformation.h>
#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include <ngl/Text.h>
#include "WindowParams.h"
#include <QEvent>
#include <QResizeEvent>
#include <QOpenGLWidget>
#include <memory>
#include <ngl/Obj.h>


/// @file NGLScene.h
/// @brief a basic Qt GL window class for ngl demos
/// @author Jonathan Macey
/// @version 1.0
/// @date 10/10/10
/// Revision History :
/// Initial Version 10/10/10 (Binary day ;-0 )
/// @class GLWindow
/// @brief our main glwindow widget for NGL applications all drawing elements are
/// put in this file
class NGLScene : public QOpenGLWidget
{
Q_OBJECT        // must include this if you use Qt signals/slots
public :
  /// @brief Constructor for GLWindow
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Constructor for GLWindow
  /// @param [in] _parent the parent window to create the GL context in
  //----------------------------------------------------------------------------------------------------------------------
  NGLScene(QWidget *_parent );

        /// @brief dtor
  ~NGLScene() override;
  void loadMatrixToShader(const ngl::Mat4 &_tx, const ngl::Vec4 &_colour);
  void loadMatricesToShader(ngl::Transformation tx);
public slots :
    /// @brief a slot to toggle wireframe mode
    /// @param[in] _mode the mode passed from the toggle
    /// button
    void toggleWireframe( bool _mode	 );
    /// @brief set the X rotation value
    /// @parm[in] _x the value to set
    void setXRotation( double _x	);
    /// @brief set the Y rotation value
    /// @parm[in] _y the value to set
    void setYRotation( double _y	);
    /// @brief set the Z rotation value
    /// @parm[in] _z the value to set
    void setZRotation( double _z	);
    /// @brief set the X scale value
    /// @parm[in] _x the value to set
    void setXScale( double _x	);
    /// @brief set the Y scale value
    /// @parm[in] _y the value to set
    void setYScale( double _y	);
    /// @brief set the Z scale value
    /// @parm[in] _z the value to set
    void setZScale( double _z	);

    /// @brief set the X position value
    /// @parm[in] _x the value to set
    void setXPosition( double _x	);
    /// @brief set the Y position value
    /// @parm[in] _y the value to set
    void setYPosition(double _y);
    /// @brief set the Z position value
    /// @parm[in] _z the value to set
    void setZPosition(double _z	);
    /// @brief set the draw object
    /// @param[in] _i the index of the object
    void setObjectMode(int _i);
    /// @brief a slot to set the colour
    void setColour(ngl::Vec4 col);
    /// @brief a slot to render
    void renderScene();
    ///@brief a slot to create a sphere
    void createSphere();
    ///@brief a slot to set the number of samples
    void setSamples(int _s);
    ///@brief a slot to set the number of samples
    void setXRes(int _x);
    ///@brief a slot to set the number of samples
    void setYRes(int _y);

private :
    /// @brief m_wireframe mode
    bool m_wireframe;
    /// @brief rotation data
  ngl::Vec3 m_rotation;
    /// @brief scale data
  ngl::Vec3 m_scale;
    /// @brief position data
  ngl::Vec3 m_position;
    /// @brief our object to draw
    int m_selectedObject;
    //----------------------------------------------------------------------------------------------------------------------
    // text for rendering
    //----------------------------------------------------------------------------------------------------------------------
    std::unique_ptr<ngl::Text> m_text;

    /// @brief our model
        //----------------------------------------------------------------------------------------------------------------------
    std::unique_ptr<ngl::Obj> m_mesh;
    std::vector<ngl::Vec3> vertList;

    enum class MeshType : char {SPHERE, OBJ, CUBE, TROLL};
    struct MeshData
    {
        ngl::Vec3 pos;
        ngl::Vec3 dir;
        ngl::Vec3 scale;
        ngl::Vec3 rot;
        ngl::Vec4 colour;
        MeshType type;
        float distance;
        MeshData(const ngl::Vec3 &_pos, const ngl::Vec3 &_scale, const ngl::Vec3 &_rot, const ngl::Vec4 &_colour, MeshType _type) :
            pos(_pos), scale(_scale), rot(_rot), colour(_colour), type(_type){}
        MeshData()=default;
        MeshData(const MeshData &)=default;
        ~MeshData()=default;
    };
    std::vector<MeshData> m_meshes;
    std::vector<std::vector<MeshData *>> m_collection;

    void createMeshes();

    struct Vertex{
        ngl::Vec3 pos;
        ngl::Vec4 Colour;
    };

    /// @brief number of samples
    int m_samples = 1;
    /// @brief number of samples
    int m_xRes = 1;
    /// @brief number of samples
    int m_yRes = 1;

//private slots:
//        void renderScene();

protected:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the windows params such as mouse and rotations etc
  //----------------------------------------------------------------------------------------------------------------------
  WinParams m_win;
  /// @brief  The following methods must be implimented in the sub class
  /// this is called when the window is created
  void initializeGL() override;

  /// @brief this is called whenever the window is re-sized
  /// @param[in] _w the width of the resized window
  /// @param[in] _h the height of the resized window
  void resizeGL(int _w , int _h) override;
  /// @brief this is the main gl drawing routine which is called whenever the window needs to
  // be re-drawn
  void paintGL() override;

  /// @brief our model position
  ngl::Vec3 m_modelPos;
  /// @brief our camera
  ngl::Mat4 m_view;
  ngl::Mat4 m_project;
  ngl::Vec3 m_eye;
  ngl::Vec3 m_look;
    /// @brief our transform for objects
    ngl::Transformation m_transform;
private :
  /// @brief this method is called every time a mouse is moved
  /// @param _event the Qt Event structure

  void mouseMoveEvent (QMouseEvent * _event   ) override;
  /// @brief this method is called everytime the mouse button is pressed
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure

  void mousePressEvent ( QMouseEvent *_event  ) override;

  /// @brief this method is called everytime the mouse button is released
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  void mouseReleaseEvent (QMouseEvent *_event ) override;
  void wheelEvent( QWheelEvent* _event ) override;

  void loadMatricesToShader( );

};

#endif
