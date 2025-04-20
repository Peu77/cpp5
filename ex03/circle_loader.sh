#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <percentage>"
    exit 1
fi

percentage=$1
if ! [[ "$percentage" =~ ^[0-9]+$ ]] || [ "$percentage" -lt 0 ] || [ "$percentage" -gt 100 ]; then
    echo "Error: Please provide a number between 0 and 100"
    exit 1
fi

PROGRESS_FILE="/tmp/ellipse_progress.txt"

if [ -f "$PROGRESS_FILE" ]; then
    previous_percentage=$(cat "$PROGRESS_FILE")
else
    previous_percentage=0
fi

echo "$percentage" > "$PROGRESS_FILE"

GREEN="\033[32m"
RESET="\033[0m"

cols=$(tput cols)
lines=$(tput lines)

width_radius=12
height_radius=$((width_radius / 2))
center_x=$((cols / 2))
center_y=$((lines / 2))

is_inside_ellipse() {
    local x=$1
    local y=$2
    local dx=$((x - center_x))
    local dy=$((y - center_y))

    local normalized=$(( (dx*dx*100) / (width_radius*width_radius) + (dy*dy*100) / (height_radius*height_radius) ))

    if [ $normalized -le 100 ]; then
        return 0  # Inside
    else
        return 1  # Outside
    fi
}

get_segment() {
    local x=$1
    local y=$2

    local dx=$((x - center_x))
    local dy=$((y - center_y))

    local scaled_dy=$((dy * 2))

    if [ $scaled_dy -lt 0 ] && [ $dx -ge 0 ] && [ $((-scaled_dy)) -ge $dx ]; then
        echo 0  # Top
    elif [ $scaled_dy -lt 0 ] && [ $dx -gt 0 ] && [ $((-scaled_dy)) -lt $dx ]; then
        echo 1  # Top-right
    elif [ $scaled_dy -ge 0 ] && [ $dx -gt 0 ] && [ $scaled_dy -le $dx ]; then
        echo 2  # Right
    elif [ $scaled_dy -gt 0 ] && [ $dx -gt 0 ] && [ $scaled_dy -gt $dx ]; then
        echo 3  # Bottom-right
    elif [ $scaled_dy -gt 0 ] && [ $dx -le 0 ] && [ $scaled_dy -ge $((-dx)) ]; then
        echo 4  # Bottom
    elif [ $scaled_dy -gt 0 ] && [ $dx -lt 0 ] && [ $scaled_dy -lt $((-dx)) ]; then
        echo 5  # Bottom-left
    elif [ $scaled_dy -le 0 ] && [ $dx -lt 0 ] && [ $((-scaled_dy)) -le $((-dx)) ]; then
        echo 6  # Left
    else
        echo 7  # Top-left
    fi
}

previous_segments=$((previous_percentage * 8 / 100))
current_segments=$((percentage * 8 / 100))

[ "$previous_percentage" -eq 100 ] && previous_segments=8
[ "$percentage" -eq 100 ] && current_segments=8

if [ ! -f "$PROGRESS_FILE.drawn" ] || [ "$current_segments" -lt "$previous_segments" ]; then
    clear

    for ((y = center_y - height_radius - 1; y <= center_y + height_radius + 1; y++)); do
        for ((x = center_x - width_radius - 1; x <= center_x + width_radius + 1; x++)); do
            if is_inside_ellipse $x $y; then
                tput cup $y $x
                segment=$(get_segment $x $y)
                if [ "$segment" -lt "$current_segments" ]; then
                    echo -ne "${GREEN}█${RESET}"
                else
                    echo -ne "█"
                fi
            fi
        done
    done

    touch "$PROGRESS_FILE.drawn"
else
    for ((y = center_y - height_radius - 1; y <= center_y + height_radius + 1; y++)); do
        for ((x = center_x - width_radius - 1; x <= center_x + width_radius + 1; x++)); do
            if is_inside_ellipse $x $y; then
                segment=$(get_segment $x $y)
                if [ "$segment" -ge "$previous_segments" ] && [ "$segment" -lt "$current_segments" ]; then
                    tput cup $y $x
                    echo -ne "${GREEN}█${RESET}"
                fi
            fi
        done
    done
fi

tput cup $center_y $((center_x - 2))
echo -n "$percentage%"

tput cup $((lines - 1)) 0

