#ifndef MDSTATE_H
#define MDSTATE_H

#include "src/databundle.h"
#include <QVector3D>
//#include <QArray>
//#include <QColor4ub>
#include <QVector2D>
#include <QMap>


class MDState : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool showWater READ showWater WRITE setShowWater NOTIFY showWaterChanged)

public:
    MDState(QObject *parent = 0);
    ~MDState();

    void addAtom(QVector3D positions, char *atomType, bool addPeriodicCopy = false, QVector3D systemSize = QVector3D(0,0,0));
    void addAtoms(QArray<QVector3D> positions, QArray<char *>atomTypes, bool addPeriodicCopy = false, QVector3D systemSize = QVector3D(0,0,0));
    int numberOfAtoms();

    bool showWater() const
    {
        return m_showWater;
    }
    void buildVertexBundle();

    QArray<DataBundle *> *dataBundles();
public slots:
    void setShowWater(bool arg)
    {
        if (m_showWater != arg) {
            m_showWater = arg;
            emit showWaterChanged(arg);
        }
    }
signals:
    void showWaterChanged(bool arg);
private:
    QMap<QString, DataBundle*> m_atomTypeToDataBundle;

    QArray<DataBundle*> m_dataBundles;
    QArray<DataBundle*> m_dataBundlesNoWater;

    QMap<QString, QColor> colorMap;
    QMap<QString, QVector2D> sizeMap;
    bool m_showWater;
};

#endif // EXAMPLEDATASOURCE_H
