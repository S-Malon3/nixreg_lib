#!/bin/sh
ln -sf ../../scripts/hooks/pre-push .git/hooks/pre-push
ln -sf ../../scripts/hooks/commit-msg .git/hooks/commit-msg
echo "Git hooks installed."
