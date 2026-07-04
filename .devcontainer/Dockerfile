FROM osrf/ros:jazzy-desktop

# 安装常用工具
RUN apt-get update && apt-get install -y \
    git \
    vim \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

# 设置工作空间
WORKDIR /workspace

# 自动 source ROS2 环境
RUN echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc

