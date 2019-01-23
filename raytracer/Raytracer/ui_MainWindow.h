/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *s_mainWindowGridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QSpinBox *m_numSamplesBox;
    QSpinBox *m_yResBox;
    QLabel *samplesLabel;
    QPushButton *m_renderButton;
    QSpinBox *m_xResBox;
    QLabel *label;
    QLabel *label_2;
    QGroupBox *s_drawGB;
    QVBoxLayout *verticalLayout;
    QCheckBox *m_wireframe;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(972, 682);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        s_mainWindowGridLayout = new QGridLayout(centralwidget);
        s_mainWindowGridLayout->setObjectName(QStringLiteral("s_mainWindowGridLayout"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        m_numSamplesBox = new QSpinBox(groupBox);
        m_numSamplesBox->setObjectName(QStringLiteral("m_numSamplesBox"));
        m_numSamplesBox->setMinimum(1);
        m_numSamplesBox->setMaximum(999999);

        gridLayout_3->addWidget(m_numSamplesBox, 2, 1, 1, 1);

        m_yResBox = new QSpinBox(groupBox);
        m_yResBox->setObjectName(QStringLiteral("m_yResBox"));
        m_yResBox->setMinimum(1);
        m_yResBox->setMaximum(999999);
        m_yResBox->setValue(200);

        gridLayout_3->addWidget(m_yResBox, 1, 1, 1, 1);

        samplesLabel = new QLabel(groupBox);
        samplesLabel->setObjectName(QStringLiteral("samplesLabel"));

        gridLayout_3->addWidget(samplesLabel, 2, 0, 1, 1);

        m_renderButton = new QPushButton(groupBox);
        m_renderButton->setObjectName(QStringLiteral("m_renderButton"));

        gridLayout_3->addWidget(m_renderButton, 3, 1, 1, 1);

        m_xResBox = new QSpinBox(groupBox);
        m_xResBox->setObjectName(QStringLiteral("m_xResBox"));
        m_xResBox->setMinimum(1);
        m_xResBox->setMaximum(999999);
        m_xResBox->setValue(400);

        gridLayout_3->addWidget(m_xResBox, 0, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_3->addWidget(label_2, 1, 0, 1, 1);


        s_mainWindowGridLayout->addWidget(groupBox, 2, 1, 1, 1);

        s_drawGB = new QGroupBox(centralwidget);
        s_drawGB->setObjectName(QStringLiteral("s_drawGB"));
        verticalLayout = new QVBoxLayout(s_drawGB);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        m_wireframe = new QCheckBox(s_drawGB);
        m_wireframe->setObjectName(QStringLiteral("m_wireframe"));

        verticalLayout->addWidget(m_wireframe);


        s_mainWindowGridLayout->addWidget(s_drawGB, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        s_mainWindowGridLayout->addItem(verticalSpacer, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        s_mainWindowGridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 972, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Ray Tracer", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Render", nullptr));
        samplesLabel->setText(QApplication::translate("MainWindow", "Number Of Samples", nullptr));
        m_renderButton->setText(QApplication::translate("MainWindow", "Render Scene", nullptr));
        label->setText(QApplication::translate("MainWindow", "X Resolution", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Y Resolution", nullptr));
        s_drawGB->setTitle(QApplication::translate("MainWindow", "Draw", nullptr));
        m_wireframe->setText(QApplication::translate("MainWindow", "WireFrame", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
