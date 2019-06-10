#include "transform.h"
#include <QDebug>

const QVector3D Transform::LocalForward(0.0f, 0.0f, 1.0f);
const QVector3D Transform::LocalUp(0.0f, 1.0f, 0.0f);
const QVector3D Transform::LocalRight(1.0f, 0.0f, 0.0f);

Transform::Transform() : Component(Component::Type::Transform),m_dirty(true), m_scale(1.0f, 1.0f, 1.0f) {}

// Transform By (Add/Scale)
void Transform::translate(const QVector3D &dt)
{
  m_dirty = true;
  m_translation += dt;
}

void Transform::scale(const QVector3D &ds)
{
  m_dirty = true;
  m_scale *= ds;
}

void Transform::rotate(const QQuaternion &dr)
{
  m_dirty = true;
  m_rotation = dr * m_rotation;
}

void Transform::grow(const QVector3D &ds)
{
  m_dirty = true;
  m_scale += ds;
}

// Transform To (Setters)
void Transform::setTranslation(const QVector3D &t)
{
  m_dirty = true;
  m_translation = t;
}

void Transform::setScale(const QVector3D &s)
{
  m_dirty = true;
  m_scale = s;
}

void Transform::setRotation(const QQuaternion &r)
{
  m_dirty = true;
  m_rotation = r;
}

// Accessors
const QMatrix4x4 &Transform::toMatrix()
{
  if (m_dirty)
  {
    m_dirty = false;
    m_world.setToIdentity();
    m_world.translate(m_translation);
    m_world.rotate(m_rotation);
    m_world.scale(m_scale);
  }
  return m_world;
}

// Queries
QVector3D Transform::forward() const
{
  return m_rotation.rotatedVector(LocalForward);
}

QVector3D Transform::up() const
{
  return m_rotation.rotatedVector(LocalUp);
}

QVector3D Transform::right() const
{
  return m_rotation.rotatedVector(LocalRight);
}

void Transform::Save(QJsonObject &file) const
{
    file["type"] = GetType();
    file["pos_x"] = translation().x();
    file["pos_y"] = translation().y();
    file["pos_z"] = translation().z();

    file["rot_x"] = rotation().toEulerAngles().x();
    file["rot_y"] = rotation().toEulerAngles().y();
    file["rot_z"] = rotation().toEulerAngles().z();

    file["scale_x"] = scale().x();
    file["scale_y"] = scale().y();
    file["scale_z"] = scale().z();
}

void Transform::Load(const QJsonObject &file)
{
    QVector3D pos(file["pos_x"].toDouble(),file["pos_y"].toDouble(),file["pos_z"].toDouble());
    QVector3D rot(file["rot_x"].toDouble(),file["rot_y"].toDouble(),file["rot_z"].toDouble());
    QVector3D scale(file["scale_x"].toDouble(),file["scale_y"].toDouble(),file["scale_z"].toDouble());

    setTranslation(pos);
    m_rotation.fromEulerAngles(rot);
    setScale(scale);
    m_dirty = true;
}
