#!/bin/bash

echo "📤 简单上传到HelloCV仓库"
echo "=========================================="

HELLOCV_URL="https://github.com/sunnyjy1/HelloCV.git"
HELLOCV_DIR="$HOME/HelloCV_temp"

echo "🔧 步骤1: 克隆HelloCV仓库..."
git clone "$HELLOCV_URL" "$HELLOCV_DIR"

echo "📁 步骤2: 创建项目目录..."
mkdir -p "$HELLOCV_DIR/traffic_light_detection"

echo "📋 步骤3: 复制项目文件..."
cp -r src/ data/ output/ "$HELLOCV_DIR/traffic_light_detection/"
cp *.sh Dockerfile "$HELLOCV_DIR/traffic_light_detection/"
mkdir -p "$HELLOCV_DIR/traffic_light_detection/docs"
cp *.md *.txt "$HELLOCV_DIR/traffic_light_detection/docs/"

echo "🚀 步骤4: 提交到GitHub..."
cd "$HELLOCV_DIR"
git add .
git commit -m "添加交通信号灯检测项目

- 完整的OpenCV交通信号灯检测系统
- 包含源代码、数据和输出结果
- 支持Docker和本地运行
- 生成详细的分析报告"

git push origin main

echo "✅ 上传完成!"
echo "📁 仓库位置: $HELLOCV_DIR"
echo "🌐 在线查看: $HELLOCV_URL"
