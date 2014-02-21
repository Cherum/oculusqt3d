#include "mdstate.h"
#include <iostream>
// double color_list[7][3] = {{1,1,1},{230.0/255,230.0/255,0},{0,0,1},{1.0,1.0,1.0},{1,0,0},{9.0/255,92.0/255,0},{95.0/255,216.0/255,250.0/255}};
MDState::MDState():
    m_showWater(1)
{
    colorMap.insert("Si", QColor4ub(230,230,0));
    sizeMap.insert("Si",QVector2D(1.11, 1.11));

    colorMap.insert("A", QColor4ub(0,0,255));
    sizeMap.insert("A",QVector2D(0.66, 0.66));

    colorMap.insert("H", QColor4ub(255,255,255));
    sizeMap.insert("H",QVector2D(0.35, 0.35));

    colorMap.insert("O", QColor4ub(255,0,0));
    sizeMap.insert("O",QVector2D(0.66, 0.66));

    colorMap.insert("Na", QColor4ub(9,92,0));
    sizeMap.insert("Na",QVector2D(1.86, 1.86));

    colorMap.insert("Cl", QColor4ub(95,216,250));
    sizeMap.insert("Cl",QVector2D(1.02, 1.02));

    colorMap.insert("N", QColor4ub(95,216,250));
    sizeMap.insert("N",QVector2D(0.66, 0.66));
}

MDState::~MDState() {
    m_positions.clear();
    m_atomTypes.clear();
    m_colors.clear();
    m_sizes.clear();
    colorMap.clear();
    sizeMap.clear();
}

int MDState::getNumberOfAtoms() {
    return m_positions.size();
}

void MDState::reserveMemory(int numberOfAtoms) {
    m_positions.reserve(numberOfAtoms);
    m_colors.reserve(numberOfAtoms);
    m_sizes.reserve(numberOfAtoms);
    m_atomTypes.reserve(numberOfAtoms);
}

void MDState::addAtom(QVector3D positions, char *atomType) {
    m_positions.push_back(positions);
    m_atomTypes.push_back(atomType);
    QMap<std::string, QColor4ub>::const_iterator colorIterator = colorMap.find(atomType);
    if(colorIterator != colorMap.end()) m_colors.push_back(colorIterator.value());
    else m_colors.push_back(QColor4ub(255,0,0));

    QMap<std::string, QVector2D>::const_iterator sizeIterator = sizeMap.find(atomType);
    if(sizeIterator != sizeMap.end()) m_sizes.push_back(sizeIterator.value());
    else m_sizes.push_back(QVector2D(1.0,1.0));
}

void MDState::addAtoms(QArray<QVector3D> positions, QArray<char *>atomTypes) {
    // Increase length of all arrays
    reserveMemory(getNumberOfAtoms() + positions.size());

    for(int i=0; i<positions.size(); i++) {
        addAtom(positions.at(i), atomTypes.at(i));
    }

}

void MDState::buildVertexBundle() {
    m_vertexBundle = QGLVertexBundle();
    m_vertexBundle.addAttribute(QGL::Position, m_positions);
    m_vertexBundle.addAttribute(QGL::Color, m_colors);
    m_vertexBundle.addAttribute(QGL::CustomVertex0, m_sizes);
}

QGLVertexBundle *MDState::vertexBundle()
{
    return &m_vertexBundle;
}

const QArray<QVector3D> &MDState::getPositions() {
    return m_positions;
}

const QArray<QColor4ub> &MDState::getColors() {
    return m_colors;
}

const QArray<QVector2D> &MDState::getSizes() {
    return m_sizes;
}
