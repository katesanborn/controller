#!/usr/bin/env bash
set -euo pipefail

BRANCH="ros_package"
ARCHIVE="controller.tgz"
EXTRACTED_DIR="controller"

ORIGINAL_BRANCH=$(git rev-parse --abbrev-ref HEAD)
echo "Current branch: $ORIGINAL_BRANCH"

# --- 1. Run MATLAB ---
echo "Running MATLAB script..."
matlab -batch "addpath(pwd); run('generate_ros_package.m')"

# --- 2. Verify output ---
if [ ! -f "$ARCHIVE" ]; then
  echo "Error: $ARCHIVE not found!"
  exit 1
fi

echo "Found archive: $ARCHIVE"

# --- 3. Git setup ---
git rev-parse --is-inside-work-tree > /dev/null
git config user.name "github-actions"
git config user.email "actions@github.com"

git fetch origin || true

# --- 4. Checkout branch ---
if git show-ref --verify --quiet refs/heads/$BRANCH; then
  git checkout "$BRANCH"
elif git ls-remote --exit-code --heads origin "$BRANCH" > /dev/null 2>&1; then
  git checkout -b "$BRANCH" "origin/$BRANCH"
else
  git checkout --orphan "$BRANCH"
fi

# --- 5. Extract safely ---
TMP_DIR=$(mktemp -d)
echo "Extracting into $TMP_DIR"

tar -xzf "$ARCHIVE" -C "$TMP_DIR"

GEN_PATH="$TMP_DIR/$EXTRACTED_DIR"

if [ ! -d "$GEN_PATH" ]; then
  echo "Error: generated folder missing in archive"
  rm -rf "$TMP_DIR"
  exit 1
fi

# --- 6. SELECTIVE DELETE (ONLY GENERATED AREAS) ---

echo "Removing old generated files only..."

rm -rf include/*
rm -rf src/*
rm -f CMakeLists.txt package.xml packageInfo.mat

# --- 7. Copy new generated content ---

echo "Updating generated files..."

cp -r "$GEN_PATH/include" .
cp -r "$GEN_PATH/src" .

cp "$GEN_PATH/CMakeLists.txt" .
cp "$GEN_PATH/package.xml" .
cp "$GEN_PATH/packageInfo.mat" .

rm -rf "$TMP_DIR"

# --- 8. Commit changes ---
git add -A

if git diff --cached --quiet; then
  echo "No changes to commit"
else
  git commit -m "Update generated ROS package (preserve custom files)"
fi

# --- 9. Push ---
echo "Pushing branch..."
git push origin "$BRANCH"

# --- 10. Restore branch ---
git checkout "$ORIGINAL_BRANCH"

echo "Done."