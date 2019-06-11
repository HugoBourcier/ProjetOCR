/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionQuitter;
    QAction *actionOpenFile;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QLabel *statusLabel;
    QProgressBar *progressBar;
    QLabel *fullImageView;
    QPushButton *openFileBtn;
    QPushButton *analyzeBtn;
    QVBoxLayout *verticalLayout_7;
    QPushButton *btnIdentifyAll_2;
    QLabel *lblIdentifyAll_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *charCombo;
    QHBoxLayout *horizontalLayout;
    QLabel *charLabel;
    QVBoxLayout *verticalLayout_5;
    QLabel *lblRatio;
    QLabel *lblClosedZones;
    QLabel *lblCorners;
    QLabel *label_3;
    QLabel *label_4;
    QSlider *knnSlider;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_14;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_16;
    QLabel *label_15;
    QLabel *label_17;
    QLabel *label_18;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *closedZonesEdit;
    QLineEdit *ratioEdit;
    QLineEdit *cornersEdit;
    QLineEdit *pixelMapEdit;
    QPushButton *algoBtn;
    QHBoxLayout *horizontalLayout_2;
    QLabel *knnResLabel;
    QVBoxLayout *verticalLayout_4;
    QLabel *knnVerdictLabel;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *knnVerdictEdit;
    QPushButton *addToDBBtn;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->setWindowModality(Qt::WindowModal);
        MainWindowClass->resize(821, 752);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindowClass->sizePolicy().hasHeightForWidth());
        MainWindowClass->setSizePolicy(sizePolicy);
        MainWindowClass->setMinimumSize(QSize(420, 300));
        MainWindowClass->setMaximumSize(QSize(821, 760));
        MainWindowClass->setStyleSheet(QString::fromUtf8("background-color:grey"));
        actionQuitter = new QAction(MainWindowClass);
        actionQuitter->setObjectName(QString::fromUtf8("actionQuitter"));
        actionOpenFile = new QAction(MainWindowClass);
        actionOpenFile->setObjectName(QString::fromUtf8("actionOpenFile"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Bahnschrift SemiBold SemiConden"));
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setMargin(10);

        gridLayout->addWidget(label, 0, 0, 1, 3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(40, -1, 40, -1);
        statusLabel = new QLabel(centralWidget);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(statusLabel->sizePolicy().hasHeightForWidth());
        statusLabel->setSizePolicy(sizePolicy1);
        statusLabel->setMaximumSize(QSize(16777215, 16777215));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Corbel Light"));
        font1.setPointSize(13);
        statusLabel->setFont(font1);
        statusLabel->setStyleSheet(QString::fromUtf8("color:white"));

        verticalLayout->addWidget(statusLabel);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        sizePolicy1.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy1);
        progressBar->setMinimum(0);
        progressBar->setMaximum(100);
        progressBar->setValue(0);
        progressBar->setTextVisible(false);
        progressBar->setInvertedAppearance(false);

        verticalLayout->addWidget(progressBar);

        fullImageView = new QLabel(centralWidget);
        fullImageView->setObjectName(QString::fromUtf8("fullImageView"));
        sizePolicy.setHeightForWidth(fullImageView->sizePolicy().hasHeightForWidth());
        fullImageView->setSizePolicy(sizePolicy);
        fullImageView->setMinimumSize(QSize(300, 300));
        fullImageView->setMaximumSize(QSize(800, 16777215));
        fullImageView->setAutoFillBackground(false);
        fullImageView->setStyleSheet(QString::fromUtf8("border : 1px solid black;\n"
"background-color: white;"));
        fullImageView->setMargin(0);

        verticalLayout->addWidget(fullImageView);

        openFileBtn = new QPushButton(centralWidget);
        openFileBtn->setObjectName(QString::fromUtf8("openFileBtn"));
        openFileBtn->setAutoFillBackground(false);
        openFileBtn->setStyleSheet(QString::fromUtf8("background-color:black; color:white;"));

        verticalLayout->addWidget(openFileBtn);

        analyzeBtn = new QPushButton(centralWidget);
        analyzeBtn->setObjectName(QString::fromUtf8("analyzeBtn"));
        analyzeBtn->setStyleSheet(QString::fromUtf8("background-color:black;color:white;"));

        verticalLayout->addWidget(analyzeBtn);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        btnIdentifyAll_2 = new QPushButton(centralWidget);
        btnIdentifyAll_2->setObjectName(QString::fromUtf8("btnIdentifyAll_2"));
        btnIdentifyAll_2->setStyleSheet(QString::fromUtf8("background-color:black;color:white;"));

        verticalLayout_7->addWidget(btnIdentifyAll_2);

        lblIdentifyAll_2 = new QLabel(centralWidget);
        lblIdentifyAll_2->setObjectName(QString::fromUtf8("lblIdentifyAll_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lblIdentifyAll_2->sizePolicy().hasHeightForWidth());
        lblIdentifyAll_2->setSizePolicy(sizePolicy2);
        lblIdentifyAll_2->setMinimumSize(QSize(200, 100));
        lblIdentifyAll_2->setMaximumSize(QSize(300, 100));
        QFont font2;
        font2.setPointSize(14);
        lblIdentifyAll_2->setFont(font2);
        lblIdentifyAll_2->setStyleSheet(QString::fromUtf8("background-color:white; border: 1px solid black;color:red;"));
        lblIdentifyAll_2->setAlignment(Qt::AlignCenter);
        lblIdentifyAll_2->setWordWrap(true);

        verticalLayout_7->addWidget(lblIdentifyAll_2);


        verticalLayout->addLayout(verticalLayout_7);


        gridLayout->addLayout(verticalLayout, 3, 0, 1, 2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_3->setContentsMargins(0, -1, -1, -1);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, -1, -1, 20);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_2);

        charCombo = new QComboBox(centralWidget);
        charCombo->setObjectName(QString::fromUtf8("charCombo"));
        sizePolicy.setHeightForWidth(charCombo->sizePolicy().hasHeightForWidth());
        charCombo->setSizePolicy(sizePolicy);
        charCombo->setMinimumSize(QSize(200, 0));

        horizontalLayout_3->addWidget(charCombo);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(25, -1, 25, -1);
        charLabel = new QLabel(centralWidget);
        charLabel->setObjectName(QString::fromUtf8("charLabel"));
        charLabel->setEnabled(true);
        sizePolicy.setHeightForWidth(charLabel->sizePolicy().hasHeightForWidth());
        charLabel->setSizePolicy(sizePolicy);
        charLabel->setMinimumSize(QSize(150, 150));
        charLabel->setMaximumSize(QSize(150, 150));
        charLabel->setLayoutDirection(Qt::LeftToRight);
        charLabel->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"background-color:white;"));
        charLabel->setScaledContents(false);
        charLabel->setAlignment(Qt::AlignCenter);
        charLabel->setMargin(0);

        horizontalLayout->addWidget(charLabel);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        lblRatio = new QLabel(centralWidget);
        lblRatio->setObjectName(QString::fromUtf8("lblRatio"));
        sizePolicy.setHeightForWidth(lblRatio->sizePolicy().hasHeightForWidth());
        lblRatio->setSizePolicy(sizePolicy);
        lblRatio->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(lblRatio);

        lblClosedZones = new QLabel(centralWidget);
        lblClosedZones->setObjectName(QString::fromUtf8("lblClosedZones"));
        sizePolicy.setHeightForWidth(lblClosedZones->sizePolicy().hasHeightForWidth());
        lblClosedZones->setSizePolicy(sizePolicy);
        lblClosedZones->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(lblClosedZones);

        lblCorners = new QLabel(centralWidget);
        lblCorners->setObjectName(QString::fromUtf8("lblCorners"));
        sizePolicy.setHeightForWidth(lblCorners->sizePolicy().hasHeightForWidth());
        lblCorners->setSizePolicy(sizePolicy);
        lblCorners->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(lblCorners);


        horizontalLayout->addLayout(verticalLayout_5);


        verticalLayout_3->addLayout(horizontalLayout);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(label_3);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(label_4);

        knnSlider = new QSlider(centralWidget);
        knnSlider->setObjectName(QString::fromUtf8("knnSlider"));
        sizePolicy1.setHeightForWidth(knnSlider->sizePolicy().hasHeightForWidth());
        knnSlider->setSizePolicy(sizePolicy1);
        knnSlider->setAcceptDrops(false);
        knnSlider->setMinimum(3);
        knnSlider->setMaximum(12);
        knnSlider->setValue(7);
        knnSlider->setOrientation(Qt::Horizontal);
        knnSlider->setInvertedAppearance(false);
        knnSlider->setInvertedControls(false);
        knnSlider->setTickPosition(QSlider::TicksAbove);
        knnSlider->setTickInterval(1);

        verticalLayout_3->addWidget(knnSlider);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(-1, 10, -1, 10);
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        sizePolicy1.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy1);
        label_14->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_14);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        sizePolicy.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy);
        label_16->setAlignment(Qt::AlignCenter);
        label_16->setWordWrap(true);

        horizontalLayout_6->addWidget(label_16);

        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        sizePolicy.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy);
        label_15->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label_15);

        label_17 = new QLabel(centralWidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        sizePolicy.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy);
        label_17->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label_17);

        label_18 = new QLabel(centralWidget);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        sizePolicy.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy);
        label_18->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label_18);


        verticalLayout_6->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        closedZonesEdit = new QLineEdit(centralWidget);
        closedZonesEdit->setObjectName(QString::fromUtf8("closedZonesEdit"));
        sizePolicy.setHeightForWidth(closedZonesEdit->sizePolicy().hasHeightForWidth());
        closedZonesEdit->setSizePolicy(sizePolicy);
        closedZonesEdit->setStyleSheet(QString::fromUtf8("background-color:white"));
        closedZonesEdit->setMaxLength(3);
        closedZonesEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(closedZonesEdit);

        ratioEdit = new QLineEdit(centralWidget);
        ratioEdit->setObjectName(QString::fromUtf8("ratioEdit"));
        sizePolicy.setHeightForWidth(ratioEdit->sizePolicy().hasHeightForWidth());
        ratioEdit->setSizePolicy(sizePolicy);
        ratioEdit->setStyleSheet(QString::fromUtf8("background-color:white"));
        ratioEdit->setMaxLength(3);
        ratioEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(ratioEdit);

        cornersEdit = new QLineEdit(centralWidget);
        cornersEdit->setObjectName(QString::fromUtf8("cornersEdit"));
        sizePolicy.setHeightForWidth(cornersEdit->sizePolicy().hasHeightForWidth());
        cornersEdit->setSizePolicy(sizePolicy);
        cornersEdit->setStyleSheet(QString::fromUtf8("background-color:white"));
        cornersEdit->setMaxLength(3);
        cornersEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(cornersEdit);

        pixelMapEdit = new QLineEdit(centralWidget);
        pixelMapEdit->setObjectName(QString::fromUtf8("pixelMapEdit"));
        sizePolicy.setHeightForWidth(pixelMapEdit->sizePolicy().hasHeightForWidth());
        pixelMapEdit->setSizePolicy(sizePolicy);
        pixelMapEdit->setStyleSheet(QString::fromUtf8("background-color:white"));
        pixelMapEdit->setMaxLength(3);
        pixelMapEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(pixelMapEdit);


        verticalLayout_6->addLayout(horizontalLayout_7);


        verticalLayout_3->addLayout(verticalLayout_6);

        algoBtn = new QPushButton(centralWidget);
        algoBtn->setObjectName(QString::fromUtf8("algoBtn"));
        sizePolicy.setHeightForWidth(algoBtn->sizePolicy().hasHeightForWidth());
        algoBtn->setSizePolicy(sizePolicy);
        algoBtn->setStyleSheet(QString::fromUtf8("background-color:black;color:white;"));

        verticalLayout_3->addWidget(algoBtn);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        knnResLabel = new QLabel(centralWidget);
        knnResLabel->setObjectName(QString::fromUtf8("knnResLabel"));
        sizePolicy.setHeightForWidth(knnResLabel->sizePolicy().hasHeightForWidth());
        knnResLabel->setSizePolicy(sizePolicy);
        knnResLabel->setMinimumSize(QSize(150, 125));
        knnResLabel->setStyleSheet(QString::fromUtf8("border:1px solid black;"));

        horizontalLayout_2->addWidget(knnResLabel);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        knnVerdictLabel = new QLabel(centralWidget);
        knnVerdictLabel->setObjectName(QString::fromUtf8("knnVerdictLabel"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Bahnschrift Condensed"));
        font3.setPointSize(20);
        knnVerdictLabel->setFont(font3);
        knnVerdictLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(knnVerdictLabel);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, -1, -1, 15);
        knnVerdictEdit = new QLineEdit(centralWidget);
        knnVerdictEdit->setObjectName(QString::fromUtf8("knnVerdictEdit"));
        sizePolicy.setHeightForWidth(knnVerdictEdit->sizePolicy().hasHeightForWidth());
        knnVerdictEdit->setSizePolicy(sizePolicy);
        knnVerdictEdit->setMaximumSize(QSize(100, 100));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Bahnschrift"));
        font4.setPointSize(15);
        knnVerdictEdit->setFont(font4);
        knnVerdictEdit->setStyleSheet(QString::fromUtf8("background-color:white"));
        knnVerdictEdit->setMaxLength(1);
        knnVerdictEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(knnVerdictEdit);


        verticalLayout_4->addLayout(horizontalLayout_5);

        addToDBBtn = new QPushButton(centralWidget);
        addToDBBtn->setObjectName(QString::fromUtf8("addToDBBtn"));
        addToDBBtn->setStyleSheet(QString::fromUtf8("background-color:black;color:white;"));

        verticalLayout_4->addWidget(addToDBBtn);


        horizontalLayout_2->addLayout(verticalLayout_4);


        verticalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout_3);


        gridLayout->addLayout(verticalLayout_2, 3, 2, 1, 1);

        MainWindowClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        sizePolicy2.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy2);
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "OCR", nullptr));
        actionQuitter->setText(QApplication::translate("MainWindowClass", "Quitter...", nullptr));
        actionOpenFile->setText(QApplication::translate("MainWindowClass", "Ouvrir une image", nullptr));
        label->setText(QApplication::translate("MainWindowClass", "RECONNAISSANCE DE CARACT\303\210RES : un outil d'exp\303\251rimentation", nullptr));
        statusLabel->setText(QApplication::translate("MainWindowClass", "Status : en attente...", nullptr));
        progressBar->setFormat(QApplication::translate("MainWindowClass", "%p%", nullptr));
        fullImageView->setText(QString());
        openFileBtn->setText(QApplication::translate("MainWindowClass", "Ouvrir une image", nullptr));
        analyzeBtn->setText(QApplication::translate("MainWindowClass", "Extraire les caract\303\250res de l'image...", nullptr));
        btnIdentifyAll_2->setText(QApplication::translate("MainWindowClass", "Identifier tous les caract\303\250res...", nullptr));
        lblIdentifyAll_2->setText(QString());
        label_2->setText(QApplication::translate("MainWindowClass", "Choisir le caract\303\250re...", nullptr));
        charLabel->setText(QApplication::translate("MainWindowClass", "Aucun caract\303\250re \303\240 afficher...", nullptr));
        lblRatio->setText(QApplication::translate("MainWindowClass", "Ratio pixels noirs/pixels blancs : -", nullptr));
        lblClosedZones->setText(QApplication::translate("MainWindowClass", "Nombre de zones ferm\303\251es : -", nullptr));
        lblCorners->setText(QApplication::translate("MainWindowClass", "Nombre de coin selon Harris : -", nullptr));
        label_3->setText(QApplication::translate("MainWindowClass", "Nombre de voisins (k)", nullptr));
        label_4->setText(QApplication::translate("MainWindowClass", "3            4           5           6           7            8           9          10          11         12", nullptr));
        label_14->setText(QApplication::translate("MainWindowClass", "Poids des caract\303\251ristiques", nullptr));
        label_16->setText(QApplication::translate("MainWindowClass", "Zones ferm\303\251es :", nullptr));
        label_15->setText(QApplication::translate("MainWindowClass", "Ratio :", nullptr));
        label_17->setText(QApplication::translate("MainWindowClass", "Coins :", nullptr));
        label_18->setText(QApplication::translate("MainWindowClass", "Pixels :", nullptr));
        closedZonesEdit->setText(QApplication::translate("MainWindowClass", "250", nullptr));
        ratioEdit->setText(QApplication::translate("MainWindowClass", "2", nullptr));
        cornersEdit->setText(QApplication::translate("MainWindowClass", "4", nullptr));
        pixelMapEdit->setText(QApplication::translate("MainWindowClass", "6", nullptr));
        algoBtn->setText(QApplication::translate("MainWindowClass", "Identifier le caract\303\250re", nullptr));
        knnResLabel->setText(QApplication::translate("MainWindowClass", "R\303\251sultats du KNN...", nullptr));
        knnVerdictLabel->setText(QApplication::translate("MainWindowClass", "Verdict :", nullptr));
        addToDBBtn->setText(QApplication::translate("MainWindowClass", "Ajouter \303\240 la base de donn\303\251es...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
