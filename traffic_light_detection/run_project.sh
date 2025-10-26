#!/bin/bash

echo "🚦 交通信号灯检测项目 - 开始运行"
echo "=========================================="

# 检查Docker
if ! command -v docker &> /dev/null; then
    echo "❌ Docker未安装，请先安装Docker"
    exit 1
fi

# 构建镜像
echo "🔨 构建Docker镜像..."
docker build -t traffic-light-detector .

# 运行容器
echo "🐳 启动容器..."
docker run -it --rm \
    -v $(pwd)/data:/workspace/data \
    -v $(pwd)/output:/workspace/output \
    -v $(pwd)/src:/workspace/src \
    traffic-light-detector \
    /bin/bash -c "
    echo '=========================================='
    echo '🚦 Docker容器内开始处理...'
    echo '=========================================='
    echo '环境检查...'
    pkg-config --modversion opencv4 || pkg-config --modversion opencv || echo '使用直接链接'
    echo '编译程序...'
    mkdir -p /workspace/build
    g++ -std=c++11 /workspace/src/main.cpp -o /workspace/build/detector \$(pkg-config --cflags --libs opencv4 2>/dev/null || pkg-config --cflags --libs opencv 2>/dev/null || echo '-lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_videoio -lopencv_highgui')
    if [ \$? -eq 0 ]; then
        echo '✅ 编译成功'
        cd /workspace
        ./build/detector
    else
        echo '❌ 编译失败'
        exit 1
    fi
    "

echo ""
echo "=========================================="
echo "处理完成！检查输出文件："
echo "ls output/"
