#!/bin/bash

echo "🚦 交通信号灯检测项目 - 开始运行"
echo "=========================================="

# 检查Docker
if ! command -v docker &> /dev/null; then
    echo "❌ Docker未安装，请先安装Docker"
    exit 1
fi

# 构建Docker镜像
echo "🔨 构建Docker镜像..."
docker build -t traffic-light-detector .

# 创建必要的目录
mkdir -p data output

# 检查视频文件
if [ -f "data/TrafficLight.mp4" ]; then
    echo "✅ 找到视频文件: data/TrafficLight.mp4"
else
    echo "⚠️  未找到TrafficLight.mp4，将自动创建测试视频"
fi

# 运行Docker容器
echo "🐳 启动Docker容器..."
echo "=========================================="

docker run -it --rm \
    -v $(pwd)/data:/workspace/data \
    -v $(pwd)/output:/workspace/output \
    -v $(pwd)/src:/workspace/src \
    traffic-light-detector \
    /bin/bash -c "
    echo '🚦 Docker容器内开始处理...'
    echo '=========================================='
    
    # 检查环境
    echo '🔍 环境检查:'
    pkg-config --modversion opencv4
    which ffmpeg
    
    # 编译程序
    echo '🛠️  编译程序...'
    mkdir -p build
    g++ -std=c++11 src/main.cpp -o build/detector \$(pkg-config --cflags --libs opencv4)
    
    if [ \$? -eq 0 ]; then
        echo '✅ 编译成功!'
        echo '=========================================='
        # 运行程序
        cd /workspace
        ./build/detector
    else
        echo '❌ 编译失败'
        echo '尝试替代编译方式...'
        g++ -std=c++11 src/main.cpp -o build/detector -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_videoio -lopencv_highgui
        if [ \$? -eq 0 ]; then
            echo '✅ 编译成功 (使用直接链接)!'
            echo '=========================================='
            ./build/detector
        else
            echo '❌ 所有编译尝试都失败'
            exit 1
        fi
    fi
    "

echo ""
echo "=========================================="
echo "🎉 Docker处理完成!"
echo "📁 查看结果:"
echo "   ls output/"
echo "   ls output/detection_results/"
