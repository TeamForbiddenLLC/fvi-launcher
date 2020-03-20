#! /bin/bash

set -o errexit
set -o nounset
set +o xtrace # !


pushd dist

if [[ "$CIRCLE_BRANCH" != "master" ]]; then
  echo "Release uploading disabled for pull requests, uploading to transfer.sh instead"
  for FILE in ./*; do
    BASENAME="$(basename "${FILE}")"
    timeout 5m curl --upload-file $FILE https://transfer.sh/$BASENAME || true
    echo ""
  done
  popd
  exit 0
fi

git config --global user.email "autodeploy@circleci.com"
git config --global user.name "Circle CI"

git init
git remote add origin https://Warfork:${GITHUB_TOKEN}@github.com/Warfork/fvi-deploy-staging.git
git checkout -b continuous-${QT_TARGET}
git add ./*
git commit -m "Deployed from CircleCI"
git push -f --set-upstream origin continuous-${QT_TARGET}

popd
