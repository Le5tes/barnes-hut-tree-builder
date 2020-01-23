module.exports = api => {
  const targets = api.env('test') ? { node: 'current'} : 'node > 8, > 0.25%, not dead';
  return {
    presets: [
      [
        '@babel/preset-env',
        {
          targets: targets
        }
      ]
    ]
  }
};