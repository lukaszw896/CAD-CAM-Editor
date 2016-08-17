#include "fileio.h"


FileIO::FileIO()
{

}

void FileIO::saveModel()
{
    setlocale(LC_ALL, "C");
    fileDialog->show();
    QString path = fileDialog->getSaveFileName();
    fileDialog->close();
    QFile file(path);
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream( &file );
        stream << data.pointList.size() <<endl;
        for(int i=0;i<data.pointList.size();i++)
        {
            stream << getVec3Cords(data.pointList[i]->localTransPointCoordinates) <<endl;
        }
        stream<< QString::fromStdString(to_string(data.bezierCurveList.size() + data.bSplineList.size() + data.interBSplineList.size()
                 + data.bezierSurfaceList.size()))<<endl;

        for(int i=0;i<data.bezierCurveList.size();i++)
        {
            stream<<"BEZIERCURVE " + QString::fromStdString(data.bezierCurveList[i]->name)<<endl;
            stream<<QString::fromStdString((to_string(((BezierCurve*)data.bezierCurveList[i])->pointVector.size())))<<endl;
            for(int j=0;j<((BezierCurve*)data.bezierCurveList[i])->pointVector.size();j++)
            {

                stream<< QString::fromStdString(to_string(data.getPointListIndex(((BezierCurve*)data.bezierCurveList[i])->pointVector[j])))+ " " ;
            }
            stream<<endl;
            stream<<"END"<<endl;
        }
        for(int i=0;i<data.bSplineList.size();i++)
        {
            stream<<"BSPLINECURVE " + QString::fromStdString(data.bSplineList[i]->name) <<endl;
            stream<<QString::fromStdString((to_string(((BSpline*)data.bSplineList[i])->deBoorPoints.size())))<<endl;
            for(int j=0;j<((BSpline*)data.bSplineList[i])->deBoorPoints.size();j++)
            {

                stream<< QString::fromStdString(to_string(data.getPointListIndex(((BSpline*)data.bSplineList[i])->deBoorPoints[j])))+ " " ;
            }
            stream<<endl;
            stream<<"END"<<endl;
        }
        for(int i=0;i<data.interBSplineList.size();i++)
        {
            stream<<"INTERP " + QString::fromStdString(data.interBSplineList[i]->name) <<endl;
            stream<<QString::fromStdString((to_string(((InterBSpline*)data.interBSplineList[i])->deBoorPoints.size())))<<endl;
            for(int j=0;j<((InterBSpline*)data.interBSplineList[i])->deBoorPoints.size();j++)
            {

                stream<< QString::fromStdString(to_string(data.getPointListIndex(((InterBSpline*)data.interBSplineList[i])->deBoorPoints[j])))+ " " ;
            }
            stream<<endl;
            stream<<"END"<<endl;
        }

        //TODO saving surfaces


    }
}

void FileIO::openModel()
{
    setlocale(LC_ALL, "C");
    QString path = fileDialog->getOpenFileName();
    fileDialog->close();
    QFile file(path);
    if ( file.open(QIODevice::ReadOnly))
    {
       QTextStream in(&file);
       bool readPoints = true;
       bool readobjects = true;
       while (readPoints)
       {
          QString line = in.readLine();
          std::vector<std::string> stringVec = split(line.toStdString(), ' ');
          //printf("%s \n",x.at(0));
          if(stringVec.at(0)[0]=='#')
          //if(!strcmp(x.at(0).c_str(),"DIMENSION:"))
          {
               continue;
              /*readDim = true;
              vectorSize = stoi(x.at(1));
              nodeVector->resize(vectorSize);
              in.readLine();
              in.readLine();*/
          }
          int numOfPoints = 0;
          if(stringVec.size() == 1)
          {
            numOfPoints = stoi(stringVec.at(0));
          }
            for(int i=0;i<numOfPoints;i++)
            {
                line= in.readLine();
                stringVec = split(line.toStdString(), ' ');
                for(int j=0;j<stringVec.size();j++)
                {
                replace(stringVec.at(j).begin(),stringVec.at(j).end(),',','.');
                }
                float x = stof( stringVec.at(0));
                float y = stof(stringVec.at(1));
                float z = stof(stringVec.at(2));
                Point* point = new Point(data.camera);
                point->xPos = x;
                point->yPos = y;
                point->zPos = z;
                point->updateTranslationMatX();
                point->updateTranslationMatY();
                point->updateTranslationMatZ();
                data.addPoint(point);
            }
            readPoints = false;
       }
       while(readobjects)
       {
           QString line = in.readLine();
           std::vector<std::string> stringVec = split(line.toStdString(), ' ');
           if(stringVec.at(0)[0]=='#')
           //if(!strcmp(x.at(0).c_str(),"DIMENSION:"))
           {
                continue;
           }
           int numOfObj= 0;
           if(stringVec.size() == 1)
           {
             numOfObj = stoi(stringVec.at(0));
           }
           for(int i=0;i<numOfObj;i++)
           {
               line= in.readLine();
               stringVec = split(line.toStdString(), ' ');
               if(stringVec.at(0)[0]=='#')
               {
                    i--;
                    continue;
               }
               if(!strcmp(stringVec.at(0).c_str(),bezierCurveString.c_str()))
               {
                    loadBezierCurve(&in);
               }else if(!strcmp(stringVec.at(0).c_str(),bsplineString.c_str()))
               {
                    loadBSplineCurve(&in);
               }else if(!strcmp(stringVec.at(0).c_str(),interCurveString.c_str()))
               {
                    loadInterpCurve(&in);
               }else if(!strcmp(stringVec.at(0).c_str(),bezierSurfString.c_str()))
               {
                    loadBezierSurf(&in);
               }else if(!strcmp(stringVec.at(0).c_str(),bSplineSurfString.c_str()))
               {
                    loadBSplineSurf(&in);
               }
           }
           readobjects = false;
       }
       /*float minX =1000000000000;
       float minY=1000000000000;
       float maxX = 0;
       float maxY = 0;

       for(int i=0;i<vectorSize;i++)
       {
           QString line = in.readLine();
           std::vector<std::string> x = split(line.toStdString(), ' ');
           float xCord = (float)stof(x.at(1));
           if(xCord<minX) minX = xCord;
           if(xCord>maxX) maxX = xCord;
           float yCord = (float)stof(x.at(2));
           if(yCord<minY) minY = yCord;
           if(yCord>maxY) maxY = yCord;
           nodeVector->at(i) = Node(xCord,yCord);
       }
       oglWidget->graph = Graph(nodeVector,minX,maxX,minY,maxY);*/
       file.close();
    }else{
        std::cout << "No such file: " << path.toStdString() << std::endl;
    }
}

QString FileIO::getVec3Cords(vec3 vec)
{
    return QString::fromStdString(to_string(vec.x)+" "+to_string(vec.y)+" "+to_string(vec.z));
}

void FileIO::loadBezierCurve(QTextStream* in)
{
    BezierCurve* bezierCurve = new BezierCurve(data.camera);
    data.addObject(BEZIERCURVE,bezierCurve);
    QString line = in->readLine();
    line = in->readLine();
    std::vector<std::string> stringVec = split(line.toStdString(), ' ');
    for(int i=0;i<stringVec.size();i++)
    {
        data.addPointToBezierCurve(bezierCurve,(Point*)data.pointList[stoi(stringVec[i])]);
    }
    line = in->readLine();
    emit dataChanged();
}

void FileIO::loadBSplineCurve(QTextStream* in)
{
    BSpline* bSpline = new BSpline(data.camera);
    data.addObject(BSPLINE,bSpline);
    QString line = in->readLine();
    line = in->readLine();
    std::vector<std::string> stringVec = split(line.toStdString(), ' ');
    for(int i=0;i<stringVec.size();i++)
    {
        data.addPointToBSpline(bSpline,(Point*)data.pointList[stoi(stringVec[i])]);
    }
    line = in->readLine();
    emit dataChanged();
}

void FileIO::loadInterpCurve(QTextStream* in)
{
    InterBSpline* interBSpline = new InterBSpline(data.camera);
    data.addObject(INTERPBSPLINE,interBSpline);
    QString line = in->readLine();
    line = in->readLine();
    std::vector<std::string> stringVec = split(line.toStdString(), ' ');
    for(int i=0;i<stringVec.size();i++)
    {
        data.addPointToInterBSpline(interBSpline,(Point*)data.pointList[stoi(stringVec[i])]);
    }
    line = in->readLine();
    emit dataChanged();
}

void FileIO::loadBezierSurf(QTextStream* in)
{
   QString line = in->readLine();
   line = in->readLine();
   line = in->readLine();

}

void FileIO::loadBSplineSurf(QTextStream* in)
{
    QString line = in->readLine();
    line = in->readLine();
    line = in->readLine();
}
