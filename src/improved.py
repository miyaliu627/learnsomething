def max_area(height):
    max_area = 0
    n = len(height)

    left = 0
    right = n-1
    while left < right:
        cur_area = max(height[left], height[right]) * (right-left)
        max_area = max(cur_area, max_area)
        if height[left] > height[right]:
            right -= 1
        else:
            left -= 1

    return max_area
