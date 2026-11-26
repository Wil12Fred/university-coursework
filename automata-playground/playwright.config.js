// The page is opened straight from disk (file://); no server is needed.
// Chromium always runs headless, so no window ever opens on a desktop.
const { defineConfig } = require('@playwright/test');

module.exports = defineConfig({
  testDir: 'tests',
  reporter: 'list',
  use: { headless: true, browserName: 'chromium' },
});
