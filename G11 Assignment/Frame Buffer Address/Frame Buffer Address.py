
def framebuffer_address(x: int, y: int) -> int:
    """
    Given pixel coordinates (x, y), return the byte-offset
    into a packed 4bpp frame buffer where two pixels share one byte.
    """
    WIDTH = 1440  # pixels per row

    # 1) Compute the linear pixel index in row-major order
    pixel_index = y * WIDTH + x

    # 2) Two pixels per byte -> divide index by 2 (integer division)
    byte_offset = pixel_index // 2

    return byte_offset

# Test the function
if __name__ == "__main__":
    # Test with some pixel coordinates
    x = 600
    y = 200
    byte_offset = framebuffer_address(x, y)
    print(f"Byte offset for pixel ({x}, {y}): {byte_offset}")