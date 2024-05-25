from PIL import Image

def save_image_rgb_to_text(image_path):
    # 打开图像
    image = Image.open(image_path)
    # 确保图像尺寸是240x240
    if image.size != (240, 240):
        raise ValueError("Image size must be 240x240")
    
    # 获取图像的像素数据
    pixels = image.load()
    
    # 获取图像文件名（不带扩展名）
    base_filename = image_path.rsplit('.', 1)[0]
    # 创建输出文件名
    output_file = f"{base_filename}.txt"
    
    # 打开输出文件
    with open(output_file, 'w') as file:
        # 遍历每个像素
        for y in range(240):
            for x in range(240):
                r, g, b = pixels[x, y]
                # 将RGB值以空格分隔的格式写入文件
                file.write(f"{r} {g} {b} ")
    
    print(f"RGB values saved to {output_file}")

# 使用示例
image_path = 'image.png'  # 将这里替换为你的图片路径
save_image_rgb_to_text(image_path)
