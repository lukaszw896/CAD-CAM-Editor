#ifndef FILEIO_H
#define FILEIO_H
#include "Data/drawableobjectsdata.h"
#include <QFileDialog>
#include <QTextStream>
#include <string.h>
#include <sstream>
#include <iostream>
#include <locale.h>
#include <QObject>

using namespace std;

class FileIO : public QObject
{
  Q_OBJECT
public:
    FileIO();
    void saveModel();
    void openModel();
    QString getVec3Cords(vec3);

signals:
    void dataChanged();

private:
    string bezierCurveString = "BEZIERCURVE";
    string bsplineString = "BSPLINECURVE";
    string interCurveString = "INTERP";
    string bezierSurfString = "BEZIERSURF";
    string bSplineSurfString = "BSPLINESURF";
    DrawableObjectsData& data = DrawableObjectsData::getInstance();
    QFileDialog* fileDialog = new QFileDialog();
    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }

    void loadBezierCurve(QTextStream*);
    void loadBSplineCurve(QTextStream*);
    void loadInterpCurve(QTextStream*);
    void loadBezierSurf(QTextStream*);
    void loadBSplineSurf(QTextStream*);


    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, elems);
        return elems;
    }
};

#endif // FILEIO_H
