#!/usr/bin/env bash

set -u

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BIN="$ROOT_DIR/cub3D"
TIMEOUT_SECONDS="${TIMEOUT_SECONDS:-2}"

GREEN="$(printf '\033[32m')"
RED="$(printf '\033[31m')"
YELLOW="$(printf '\033[33m')"
RESET="$(printf '\033[0m')"

pass=0
fail=0
skip=0

cleanup_permission_fixtures() {
	chmod 644 "$ROOT_DIR/tests/errors/file/permission_denied.cub" 2>/dev/null
	chmod 644 "$ROOT_DIR/tests/fixtures/unreadable_texture.xpm" 2>/dev/null
}

trap cleanup_permission_fixtures EXIT

make -C "$ROOT_DIR" clean >/dev/null || {
	printf '%sFAIL%s clean failed\n' "$RED" "$RESET"
	exit 1
}

make -C "$ROOT_DIR" >/dev/null || {
	printf '%sFAIL%s build failed\n' "$RED" "$RESET"
	exit 1
}

chmod 000 "$ROOT_DIR/tests/errors/file/permission_denied.cub" 2>/dev/null
chmod 000 "$ROOT_DIR/tests/fixtures/unreadable_texture.xpm" 2>/dev/null

expected_error_message() {
	local label="$1"

	case "$label" in
		tests/errors/args/*) printf 'Usage: ./cub3D <map.cub>' ;;
		tests/errors/file/invalid_extension.cu|tests/errors/file/invalid_extension.cubd|tests/errors/file/no_extension|tests/errors/file/uppercase_extension.CUB) printf 'Map file must have .cub extension' ;;
		tests/errors/file/does_not_exist.cub|tests/errors/file/permission_denied.cub) printf 'Cannot open .cub file' ;;
		tests/errors/header/duplicate_*texture.cub|tests/errors/header/duplicate_identifier.cub) printf 'Duplicate texture definition' ;;
		tests/errors/header/duplicate_*color.cub) printf 'Duplicate color definition' ;;
		tests/errors/header/missing_*texture.cub) printf 'Missing texture definition (NO/SO/WE/EA)' ;;
		tests/errors/header/missing_floor_color.cub) printf 'Missing floor color (F)' ;;
		tests/errors/header/missing_ceiling_color.cub) printf 'Missing ceiling color (C)' ;;
		tests/errors/header/map_before_required_header.cub) printf 'Missing texture definition (NO/SO/WE/EA)' ;;
		tests/errors/header/header_after_map.cub) printf 'Invalid character in map' ;;
		tests/errors/header/*) printf 'Unknown header line' ;;
		tests/errors/color/*range_high.cub) printf 'Color value out of range (0-255)' ;;
		tests/errors/color/*range_low.cub|tests/errors/color/negative_value.cub|tests/errors/color/*non_numeric.cub|tests/errors/color/floor_trailing_junk.cub) printf 'Color values must be numeric' ;;
		tests/errors/color/missing_*_values.cub) printf 'Missing color values' ;;
		tests/errors/color/invalid_format.cub) printf 'Color values must be numeric' ;;
		tests/errors/color/empty_component.cub|tests/errors/color/too_few_values.cub|tests/errors/color/too_many_values.cub|tests/errors/color/trailing_comma.cub|tests/errors/color/wrong_separator.cub) printf 'Color must be R,G,B' ;;
		tests/errors/texture/empty_path.cub) printf 'Empty texture path' ;;
		tests/errors/texture/*) printf 'Failed to load texture (must be .xpm)' ;;
		tests/errors/map/empty_map.cub) printf 'Map is empty' ;;
		tests/errors/map/invalid_character.cub|tests/errors/map/tab_inside_map.cub) printf 'Invalid character in map' ;;
		tests/errors/map/multiple_players.cub|tests/errors/map/no_player.cub) printf 'Player count must be exactly 1' ;;
		tests/errors/map/map_too_tall.cub) printf 'Map exceeds maximum height' ;;
		tests/errors/map/map_starts_with_floor.cub) printf 'Unknown header line' ;;
		tests/errors/map/*) printf 'Map is not closed' ;;
		*) printf 'Error' ;;
	esac
}

run_argv_case() {
	local label="$1"
	local tmp
	local status
	local expected

	tmp="$(mktemp)"
	if [[ "$label" == "tests/errors/args/no_argument" ]]; then
		timeout "$TIMEOUT_SECONDS" "$BIN" >"$tmp.out" 2>"$tmp.err"
	else
		timeout "$TIMEOUT_SECONDS" "$BIN" "$ROOT_DIR/tests/valid/minimal.cub" "$ROOT_DIR/tests/valid/minimal.cub" >"$tmp.out" 2>"$tmp.err"
	fi
	status=$?
	expected="$(expected_error_message "$label")"
	if [[ $status -ne 0 ]] && grep -q '^Error$' "$tmp.err" && grep -Fq "$expected" "$tmp.err"; then
		printf '%sPASS%s error %s\n' "$GREEN" "$RESET" "$label"
		pass=$((pass + 1))
	else
		printf '%sFAIL%s error %s exited %d; expected: %s\n' "$RED" "$RESET" "$label" "$status" "$expected"
		sed 's/^/  stderr: /' "$tmp.err"
		fail=$((fail + 1))
	fi
	rm -f "$tmp" "$tmp.out" "$tmp.err"
}

run_one() {
	local expected="$1"
	local path="$2"
	local label="${path#$ROOT_DIR/}"
	local tmp
	local status
	local expected_msg

	tmp="$(mktemp)"
	timeout "$TIMEOUT_SECONDS" "$BIN" "$path" >"$tmp.out" 2>"$tmp.err"
	status=$?

	if [[ "$expected" == "valid" ]]; then
		if [[ $status -eq 0 || $status -eq 124 ]]; then
			printf '%sPASS%s valid %s\n' "$GREEN" "$RESET" "$label"
			pass=$((pass + 1))
		elif grep -q 'mlx_init failed' "$tmp.err"; then
			printf '%sPASS%s valid %s (parsed; MLX unavailable)\n' "$GREEN" "$RESET" "$label"
			pass=$((pass + 1))
		else
			printf '%sFAIL%s valid %s exited %d\n' "$RED" "$RESET" "$label" "$status"
			sed 's/^/  stderr: /' "$tmp.err"
			fail=$((fail + 1))
		fi
	else
		expected_msg="$(expected_error_message "$label")"
		if [[ "$label" == tests/errors/texture/* ]] && [[ "$label" != "tests/errors/texture/empty_path.cub" ]] && grep -q 'mlx_init failed' "$tmp.err"; then
			printf '%sSKIP%s error %s (MLX unavailable before texture loading)\n' "$YELLOW" "$RESET" "$label"
			skip=$((skip + 1))
		elif [[ $status -ne 0 ]] && grep -q '^Error$' "$tmp.err" && grep -Fq "$expected_msg" "$tmp.err"; then
			printf '%sPASS%s error %s\n' "$GREEN" "$RESET" "$label"
			pass=$((pass + 1))
		else
			printf '%sFAIL%s error %s exited %d; expected: %s\n' "$RED" "$RESET" "$label" "$status" "$expected_msg"
			sed 's/^/  stderr: /' "$tmp.err"
			fail=$((fail + 1))
		fi
	fi

	rm -f "$tmp" "$tmp.out" "$tmp.err"
}

while IFS= read -r file; do
	run_one valid "$file"
done < <(find "$ROOT_DIR/tests/valid" -type f -name '*.cub' | sort)

run_argv_case "tests/errors/args/no_argument"
run_argv_case "tests/errors/args/too_many_arguments"

while IFS= read -r file; do
	run_one error "$file"
done < <(find "$ROOT_DIR/tests/errors" -type f ! -path '*/args/*' ! -path '*/file/file_not_found.cub' | sort)

run_one error "$ROOT_DIR/tests/errors/file/does_not_exist.cub"

printf '\nsummary: %s passed, %s failed, %s skipped\n' "$pass" "$fail" "$skip"
if [[ $fail -ne 0 ]]; then
	exit 1
fi
