#include "CQssFileAdaption.h"

CQssFileAdaption::CQssFileAdaption()
{

}

CQssFileAdaption::~CQssFileAdaption()
{

}

CQssFileAdaption *CQssFileAdaption::getInstance()
{
    static CQssFileAdaption instance;

    return &instance;
}


QString CQssFileAdaption::getMainWindow()
{
    return QString("./qss/style_mainWindow.qss");
}

QString CQssFileAdaption:: getLog()
{
    return QString("./qss/style_log.qss");
}

QString CQssFileAdaption::getCommunication()
{
    return QString("./qss/style_communication.qss");
}

