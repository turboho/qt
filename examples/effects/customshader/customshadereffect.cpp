/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the either Technology Preview License Agreement or the
** Beta Release License Agreement.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#include "customshadereffect.h"
#include <QGLShaderProgram>

static char const colorizeShaderCode[] =
    "varying highp vec2 textureCoords;\n"
    "uniform sampler2D imageTexture;\n"
    "uniform lowp vec4 effectColor;\n"
    "lowp vec4 srcPixel() {\n"
    "    vec4 src = texture2D(imageTexture, textureCoords);\n"
    "    float gray = dot(src.rgb, vec3(0.212671, 0.715160, 0.072169));\n"
    "    vec4 colorize = 1.0-((1.0-gray)*(1.0-effectColor));\n"
    "    return vec4(colorize.rgb, src.a);\n"
    "}";

CustomShaderEffect::CustomShaderEffect()
    : QGraphicsShaderEffect(),
      color(Qt::red)
{
    setPixelShaderFragment(colorizeShaderCode);
}

void CustomShaderEffect::setEffectColor(const QColor& c)
{
    color = c;
    setUniformsDirty();
}

void CustomShaderEffect::setUniforms(QGLShaderProgram *program)
{
    program->setUniformValue("effectColor", color);
}