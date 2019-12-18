mkdir dist

npm run build-core
cp -r lib/js/core dist/

./node_modules/.bin/babel lib/js/src --out-dir dist/wrapper