#include "HighPre.h"
#include "ui_HighPre.h"

HighPre::HighPre(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HighPre)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    connect(ui->allControl,SIGNAL(clicked(bool)),this,SLOT(on_allControl_clicked(bool)));
    connect(ui->iconSource,SIGNAL(clicked(bool)),this,SLOT(on_iconSource_clicked(bool)));
    connect(ui->dynode,SIGNAL(clicked(bool)),this,SLOT(on_dynode_clicked(bool)));
    connect(ui->increase,SIGNAL(clicked(bool)),this,SLOT(on_increase_clicked(bool)));

}

HighPre::~HighPre()
{
    delete ui;
}

void HighPre::on_allControl_clicked(bool is_selected)
{
    if(is_selected){
        ui->dynode->SetSelected(true);
        ui->iconSource->SetSelected(true);
        ui->increase->SetSelected(true);
    }else{
        ui->dynode->SetSelected(false);
        ui->iconSource->SetSelected(false);
        ui->increase->SetSelected(false);
    }
}

void HighPre::on_iconSource_clicked(bool is_selected)
{
    if(is_selected){
        if(ui->dynode->IsSelected() && ui->increase->IsSelected())
            ui->allControl->SetSelected(true);
    }else{
        if(!ui->dynode->IsSelected() && !ui->increase->IsSelected())
            ui->allControl->SetSelected(false);
    }
}

void HighPre::on_dynode_clicked(bool is_selected)
{
    if(is_selected){
        if(ui->iconSource->IsSelected() && ui->increase->IsSelected())
            ui->allControl->SetSelected(true);
    }else{
        if(!ui->iconSource->IsSelected() && !ui->increase->IsSelected())
            ui->allControl->SetSelected(false);
    }
}

void HighPre::on_increase_clicked(bool is_selected)
{
    if(is_selected){
        if(ui->dynode->IsSelected() && ui->iconSource->IsSelected())
            ui->allControl->SetSelected(true);
    }else{
        if(!ui->dynode->IsSelected() && !ui->iconSource->IsSelected())
            ui->allControl->SetSelected(false);
    }
}
