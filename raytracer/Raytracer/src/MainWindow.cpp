#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);

  m_gl=new  NGLScene(this);

  m_ui->s_mainWindowGridLayout->addWidget(m_gl,0,0,2,1);
  //toggle wireframe signal
  connect(m_ui->m_wireframe,SIGNAL(toggled(bool)),m_gl,SLOT(toggleWireframe(bool)));

  //number of samples signal
  connect(m_ui->m_numSamplesBox,SIGNAL(valueChanged(int)),m_gl,SLOT(setSamples(int)));

  //x resolution signal
  connect(m_ui->m_xResBox,SIGNAL(valueChanged(int)),m_gl,SLOT(setXRes(int)));
  //y resolution signal
  connect(m_ui->m_yResBox,SIGNAL(valueChanged(int)),m_gl,SLOT(setYRes(int)));
  //render button signal
  connect(m_ui->m_renderButton,SIGNAL(clicked()),m_gl,SLOT(renderScene()));

}

MainWindow::~MainWindow()
{
    delete m_ui;
}
