#!/usr/bin/env bash
set -euo pipefail

BRANCH="ros_package"
ARCHIVE="controller.tgz"
EXTRACTED_DIR="controller"

# --- 1. Always lock to repo root ---
REPO_ROOT=$(git rev-parse --show-toplevel)
cd "$REPO_ROOT"

echo "Repo root: $REPO_ROOT"

ORIGINAL_BRANCH=$(git rev-parse --abbrev-ref HEAD)
echo "Current branch: $ORIGINAL_BRANCH"

# --- 2. Run MATLAB ---
echo "Running MATLAB script..."
matlab -batch "addpath(pwd); run('generate_ros_package.m')"

# --- 3. Ensure archive exists (repo root only) ---
ARCHIVE_PATH="$REPO_ROOT/$ARCHIVE"

if [ ! -f "$ARCHIVE_PATH" ]; then
  echo "Error: $ARCHIVE not found in repo root"
  exit 1
fi

echo "Found archive: $ARCHIVE_PATH"

# --- 4. Convert path safely for Git Bash tools ---
# (prevents C:\ vs /c/ issues)
if command -v cygpath >/dev/null 2>&1; then
  ARCHIVE_UNIX=$(cygpath -u "$ARCHIVE_PATH")
else
  ARCHIVE_UNIX="$ARCHIVE_PATH"
fi

# --- 5. Git setup ---
git config user.name "github-actions"
git config user.email "actions@github.com"
git fetch origin || true

# --- 6. Checkout ros_package branch ---
if git show-ref --verify --quiet refs/heads/$BRANCH; then
  echo "Switching to existing branch $BRANCH"
  git checkout "$BRANCH"
elif git ls-remote --exit-code --heads origin "$BRANCH" > /dev/null 2>&1; then
  echo "Checking out remote branch $BRANCH"
  git checkout -b "$BRANCH" "origin/$BRANCH"
else
  echo "Creating orphan branch $BRANCH"
  git checkout --orphan "$BRANCH"
fi

# --- 7. Extract safely into temp directory ---
TMP_DIR=$(mktemp -d)
echo "Extracting archive: $ARCHIVE_UNIX -> $TMP_DIR"

if ! tar -xzf "$ARCHIVE_UNIX" -C "$TMP_DIR"; then
  echo "Error: failed to extract archive (likely corrupted .tgz)"
  rm -rf "$TMP_DIR"
  exit 1
fi

GEN_PATH="$TMP_DIR/$EXTRACTED_DIR"

if [ ! -d "$GEN_PATH" ]; then
  echo "Error: expected controller folder not found in archive"
  rm -rf "$TMP_DIR"
  exit 1
fi

# --- 8. SAFELY update ONLY generated ROS files ---
echo "Updating generated ROS package files (preserving custom content)..."

# Only remove known generated artifacts (NOT whole repo)
rm -rf include src
rm -f CMakeLists.txt package.xml packageInfo.mat

# Copy fresh generated content
cp -r "$GEN_PATH/include" .
cp -r "$GEN_PATH/src" .

cp "$GEN_PATH/CMakeLists.txt" .
cp "$GEN_PATH/package.xml" .
cp "$GEN_PATH/packageInfo.mat" .

rm -rf "$TMP_DIR"

# --- 9. Stage ONLY ROS package files (prevents leakage) ---
echo "Staging ROS package files only..."

git add include src CMakeLists.txt package.xml packageInfo.mat

# --- 10. Commit if needed ---
if git diff --cached --quiet; then
  echo "No changes to commit"
else
  git commit -m "Update ROS package from MATLAB generation"
fi

# --- 11. Push ---
echo "Pushing branch $BRANCH..."
git push origin "$BRANCH"

# --- 12. Return to original branch ---
git checkout "$ORIGINAL_BRANCH"

echo "Done."