/********************************************************************************
** Form generated from reading UI file 'qkd_param.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QKD_PARAM_H
#define UI_QKD_PARAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QKD_param
{
public:
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *QKD_timeA;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *QKD_numbA;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpinBox *QKD_phA;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpinBox *QKD_iwA;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QSpinBox *QKD_pxqA;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QSpinBox *QKD_zeroA;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_7;
    QDoubleSpinBox *QKD_timeB;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_17;
    QSpinBox *QKD_numbB;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_15;
    QSpinBox *QKD_phB;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_13;
    QSpinBox *QKD_iwB;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_11;
    QSpinBox *QKD_pxqB;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_8;
    QSpinBox *QKD_zeroB;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_9;
    QDoubleSpinBox *QKD_timeC;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_18;
    QSpinBox *QKD_numbC;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_16;
    QSpinBox *QKD_phC;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_14;
    QSpinBox *QKD_iwC;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_12;
    QSpinBox *QKD_pxqC;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_10;
    QSpinBox *QKD_zeroC;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_19;
    QSlider *QKD_DB;
    QPushButton *hdf5;

    void setupUi(QWidget *QKD_param)
    {
        if (QKD_param->objectName().isEmpty())
            QKD_param->setObjectName(QString::fromUtf8("QKD_param"));
        QKD_param->resize(836, 300);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QKD_param->sizePolicy().hasHeightForWidth());
        QKD_param->setSizePolicy(sizePolicy);
        QKD_param->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(80, 80, 80, 255), stop:1 rgba(50, 50, 50, 255));"));
        horizontalLayout_7 = new QHBoxLayout(QKD_param);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(QKD_param);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(label);

        QKD_timeA = new QDoubleSpinBox(QKD_param);
        QKD_timeA->setObjectName(QString::fromUtf8("QKD_timeA"));
        QKD_timeA->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));
        QKD_timeA->setDecimals(3);
        QKD_timeA->setMaximum(5000.000000000000000);

        horizontalLayout->addWidget(QKD_timeA);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(QKD_param);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(label_2);

        QKD_numbA = new QSpinBox(QKD_param);
        QKD_numbA->setObjectName(QString::fromUtf8("QKD_numbA"));
        QKD_numbA->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        QKD_numbA->setMinimum(1);
        QKD_numbA->setMaximum(500);

        horizontalLayout_2->addWidget(QKD_numbA);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(QKD_param);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(label_3);

        QKD_phA = new QSpinBox(QKD_param);
        QKD_phA->setObjectName(QString::fromUtf8("QKD_phA"));
        QKD_phA->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        QKD_phA->setMinimum(1);
        QKD_phA->setMaximum(3000);

        horizontalLayout_3->addWidget(QKD_phA);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(QKD_param);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_4->addWidget(label_4);

        QKD_iwA = new QSpinBox(QKD_param);
        QKD_iwA->setObjectName(QString::fromUtf8("QKD_iwA"));
        QKD_iwA->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        QKD_iwA->setMinimum(1);
        QKD_iwA->setMaximum(2000);

        horizontalLayout_4->addWidget(QKD_iwA);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(QKD_param);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
""));

        horizontalLayout_5->addWidget(label_5);

        QKD_pxqA = new QSpinBox(QKD_param);
        QKD_pxqA->setObjectName(QString::fromUtf8("QKD_pxqA"));
        QKD_pxqA->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        QKD_pxqA->setMinimum(1);
        QKD_pxqA->setMaximum(3);

        horizontalLayout_5->addWidget(QKD_pxqA);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_6 = new QLabel(QKD_param);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_6->addWidget(label_6);

        QKD_zeroA = new QSpinBox(QKD_param);
        QKD_zeroA->setObjectName(QString::fromUtf8("QKD_zeroA"));
        QKD_zeroA->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        QKD_zeroA->setMaximum(5000);

        horizontalLayout_6->addWidget(QKD_zeroA);


        verticalLayout->addLayout(horizontalLayout_6);


        horizontalLayout_7->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_7 = new QLabel(QKD_param);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_8->addWidget(label_7);

        QKD_timeB = new QDoubleSpinBox(QKD_param);
        QKD_timeB->setObjectName(QString::fromUtf8("QKD_timeB"));
        QKD_timeB->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));
        QKD_timeB->setDecimals(3);
        QKD_timeB->setMaximum(5000.000000000000000);

        horizontalLayout_8->addWidget(QKD_timeB);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        label_17 = new QLabel(QKD_param);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_18->addWidget(label_17);

        QKD_numbB = new QSpinBox(QKD_param);
        QKD_numbB->setObjectName(QString::fromUtf8("QKD_numbB"));
        QKD_numbB->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        QKD_numbB->setMinimum(1);
        QKD_numbB->setMaximum(500);

        horizontalLayout_18->addWidget(QKD_numbB);


        verticalLayout_2->addLayout(horizontalLayout_18);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_15 = new QLabel(QKD_param);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_16->addWidget(label_15);

        QKD_phB = new QSpinBox(QKD_param);
        QKD_phB->setObjectName(QString::fromUtf8("QKD_phB"));
        QKD_phB->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        QKD_phB->setMinimum(1);
        QKD_phB->setMaximum(3000);

        horizontalLayout_16->addWidget(QKD_phB);


        verticalLayout_2->addLayout(horizontalLayout_16);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_13 = new QLabel(QKD_param);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_14->addWidget(label_13);

        QKD_iwB = new QSpinBox(QKD_param);
        QKD_iwB->setObjectName(QString::fromUtf8("QKD_iwB"));
        QKD_iwB->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        QKD_iwB->setMinimum(1);
        QKD_iwB->setMaximum(2000);

        horizontalLayout_14->addWidget(QKD_iwB);


        verticalLayout_2->addLayout(horizontalLayout_14);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_11 = new QLabel(QKD_param);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_12->addWidget(label_11);

        QKD_pxqB = new QSpinBox(QKD_param);
        QKD_pxqB->setObjectName(QString::fromUtf8("QKD_pxqB"));
        QKD_pxqB->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        QKD_pxqB->setMinimum(1);
        QKD_pxqB->setMaximum(3);

        horizontalLayout_12->addWidget(QKD_pxqB);


        verticalLayout_2->addLayout(horizontalLayout_12);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_8 = new QLabel(QKD_param);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_9->addWidget(label_8);

        QKD_zeroB = new QSpinBox(QKD_param);
        QKD_zeroB->setObjectName(QString::fromUtf8("QKD_zeroB"));
        QKD_zeroB->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        QKD_zeroB->setMaximum(5000);

        horizontalLayout_9->addWidget(QKD_zeroB);


        verticalLayout_2->addLayout(horizontalLayout_9);


        horizontalLayout_7->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_9 = new QLabel(QKD_param);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_10->addWidget(label_9);

        QKD_timeC = new QDoubleSpinBox(QKD_param);
        QKD_timeC->setObjectName(QString::fromUtf8("QKD_timeC"));
        QKD_timeC->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));
        QKD_timeC->setDecimals(3);
        QKD_timeC->setMaximum(5000.000000000000000);

        horizontalLayout_10->addWidget(QKD_timeC);


        verticalLayout_3->addLayout(horizontalLayout_10);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        label_18 = new QLabel(QKD_param);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_19->addWidget(label_18);

        QKD_numbC = new QSpinBox(QKD_param);
        QKD_numbC->setObjectName(QString::fromUtf8("QKD_numbC"));
        QKD_numbC->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        QKD_numbC->setMinimum(1);
        QKD_numbC->setMaximum(500);

        horizontalLayout_19->addWidget(QKD_numbC);


        verticalLayout_3->addLayout(horizontalLayout_19);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        label_16 = new QLabel(QKD_param);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_17->addWidget(label_16);

        QKD_phC = new QSpinBox(QKD_param);
        QKD_phC->setObjectName(QString::fromUtf8("QKD_phC"));
        QKD_phC->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_17->addWidget(QKD_phC);


        verticalLayout_3->addLayout(horizontalLayout_17);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_14 = new QLabel(QKD_param);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_15->addWidget(label_14);

        QKD_iwC = new QSpinBox(QKD_param);
        QKD_iwC->setObjectName(QString::fromUtf8("QKD_iwC"));
        QKD_iwC->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        QKD_iwC->setMinimum(1);
        QKD_iwC->setMaximum(2000);

        horizontalLayout_15->addWidget(QKD_iwC);


        verticalLayout_3->addLayout(horizontalLayout_15);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_12 = new QLabel(QKD_param);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_13->addWidget(label_12);

        QKD_pxqC = new QSpinBox(QKD_param);
        QKD_pxqC->setObjectName(QString::fromUtf8("QKD_pxqC"));
        QKD_pxqC->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        QKD_pxqC->setMinimum(1);
        QKD_pxqC->setMaximum(3);

        horizontalLayout_13->addWidget(QKD_pxqC);


        verticalLayout_3->addLayout(horizontalLayout_13);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_10 = new QLabel(QKD_param);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_11->addWidget(label_10);

        QKD_zeroC = new QSpinBox(QKD_param);
        QKD_zeroC->setObjectName(QString::fromUtf8("QKD_zeroC"));
        QKD_zeroC->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        QKD_zeroC->setMaximum(5000);

        horizontalLayout_11->addWidget(QKD_zeroC);


        verticalLayout_3->addLayout(horizontalLayout_11);


        horizontalLayout_7->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        label_19 = new QLabel(QKD_param);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));

        horizontalLayout_20->addWidget(label_19);

        QKD_DB = new QSlider(QKD_param);
        QKD_DB->setObjectName(QString::fromUtf8("QKD_DB"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(QKD_DB->sizePolicy().hasHeightForWidth());
        QKD_DB->setSizePolicy(sizePolicy1);
        QKD_DB->setMinimumSize(QSize(76, 0));
        QKD_DB->setMaximum(1);
        QKD_DB->setOrientation(Qt::Horizontal);

        horizontalLayout_20->addWidget(QKD_DB);


        verticalLayout_4->addLayout(horizontalLayout_20);

        hdf5 = new QPushButton(QKD_param);
        hdf5->setObjectName(QString::fromUtf8("hdf5"));
        hdf5->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);"));

        verticalLayout_4->addWidget(hdf5);


        horizontalLayout_7->addLayout(verticalLayout_4);


        retranslateUi(QKD_param);

        QMetaObject::connectSlotsByName(QKD_param);
    } // setupUi

    void retranslateUi(QWidget *QKD_param)
    {
        QKD_param->setWindowTitle(QApplication::translate("QKD_param", "QKD parameters", nullptr));
        label->setText(QApplication::translate("QKD_param", "Qubit time A", nullptr));
        QKD_timeA->setSuffix(QApplication::translate("QKD_param", " [ps]", nullptr));
        label_2->setText(QApplication::translate("QKD_param", "# qubits A", nullptr));
        label_3->setText(QApplication::translate("QKD_param", "Phase time A", nullptr));
        QKD_phA->setSuffix(QApplication::translate("QKD_param", " [ps]", nullptr));
        label_4->setText(QApplication::translate("QKD_param", "Integration Win A", nullptr));
        QKD_iwA->setSuffix(QApplication::translate("QKD_param", " [ps]", nullptr));
        label_5->setText(QApplication::translate("QKD_param", "Peaks x Qubit A", nullptr));
        label_6->setText(QApplication::translate("QKD_param", "Offset A", nullptr));
        label_7->setText(QApplication::translate("QKD_param", "Qubit time B", nullptr));
        QKD_timeB->setSuffix(QApplication::translate("QKD_param", " [ps]", nullptr));
        label_17->setText(QApplication::translate("QKD_param", "# qubits B", nullptr));
        label_15->setText(QApplication::translate("QKD_param", "Phase time B", nullptr));
        QKD_phB->setSuffix(QApplication::translate("QKD_param", " [ps]", nullptr));
        label_13->setText(QApplication::translate("QKD_param", "Integration Win B", nullptr));
        QKD_iwB->setSuffix(QApplication::translate("QKD_param", " [ps]", nullptr));
        label_11->setText(QApplication::translate("QKD_param", "Peaks x Qubit B", nullptr));
        label_8->setText(QApplication::translate("QKD_param", "Offset B", nullptr));
        label_9->setText(QApplication::translate("QKD_param", "Qubit time B", nullptr));
        QKD_timeC->setSuffix(QApplication::translate("QKD_param", " [ps]", nullptr));
        label_18->setText(QApplication::translate("QKD_param", "# qubits C", nullptr));
        label_16->setText(QApplication::translate("QKD_param", "Phase time C", nullptr));
        QKD_phC->setSuffix(QApplication::translate("QKD_param", " [ps]", nullptr));
        label_14->setText(QApplication::translate("QKD_param", "Integration Win B", nullptr));
        QKD_iwC->setSuffix(QApplication::translate("QKD_param", " [ps]", nullptr));
        label_12->setText(QApplication::translate("QKD_param", "Peaks x Qubit C", nullptr));
        label_10->setText(QApplication::translate("QKD_param", "Offset C", nullptr));
        label_19->setText(QApplication::translate("QKD_param", "Save data", nullptr));
        hdf5->setText(QApplication::translate("QKD_param", "HDF5 hist save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QKD_param: public Ui_QKD_param {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QKD_PARAM_H
