module.exports = function override(config) {
    config.module.rules.forEach(rule => {
      if (rule.use) {
        rule.use = rule.use.filter(
          loader => !(loader.loader && loader.loader.includes('source-map-loader'))
        );
      }
    });
    return config;
  };
  