// Drives Pagina.html the way a user would: build the transition table of an
// automaton, derive strings, draw its graph and ask for the regular expression.
const path = require('path');
const { test, expect } = require('@playwright/test');

const PAGE = 'file://' + path.resolve(__dirname, '..', 'Pagina Automatas', 'Pagina.html');

// States are letters (q0 = A); cells hold the target state of each input.
async function buildAutomaton(page, inputs, table, accepting) {
  await page.goto(PAGE);
  await page.fill('#entradas', String(inputs));
  await page.fill('#estados', String(table.length));
  await page.click('input[value="Crear tabla"]');
  for (let q = 0; q < table.length; q++)
    for (let e = 0; e < inputs; e++) await page.fill(`#q${q}-${e}`, table[q][e]);
  await page.fill('#estado_aceptacion', accepting);
}

async function derive(page, word) {
  await page.fill('#cadena_entrada', word);
  await page.click('input[value="Derivar cadena"]');
  return page.locator('#mostrar_expresiones_libres').innerText();
}

// Parity of the 1s: A = even, B = odd; accept A.
const PARITY = [['A', 'B'], ['B', 'A']];

test('derives a string step by step and accepts it', async ({ page }) => {
  await buildAutomaton(page, 2, PARITY, 'A');
  const out = await derive(page, '11');
  expect(out.split('\n').map((l) => l.trim()).filter(Boolean)).toEqual(['A', '1B', '11A', '11', 'Verdadero.']);
});

test('rejects strings that end outside the accepting state', async ({ page }) => {
  await buildAutomaton(page, 2, PARITY, 'A');
  expect(await derive(page, '1')).toContain('Falso.');
  expect(await derive(page, '0101')).toContain('Verdadero.');
  expect(await derive(page, '0111')).toContain('Falso.');
});

test('draws one node per state and one edge per transition', async ({ page }) => {
  // 2 inputs, 3 states: the counts differ, so mixing them up shows
  const MOD3 = [['A', 'B'], ['C', 'A'], ['B', 'C']];
  await buildAutomaton(page, 2, MOD3, 'A');
  await page.click('input[value="Generar Automata de Estados Finitos"]');
  expect(await page.evaluate(() => nodes.length)).toBe(3);
  expect(await page.evaluate(() => edges.length)).toBe(6);
  const toB = await page.evaluate(() => edges.get().filter((e) => e.to === 1).length);
  expect(toB).toBe(2); // A --1--> B and C --0--> B
});

test('produces the regular expression from the README example', async ({ page }) => {
  await buildAutomaton(page, 2, PARITY, 'A');
  await derive(page, '11');
  await page.click('text=ExpresionRegular');
  await expect(page.locator('#ExRe')).toHaveText(
    '[(0|[(0)*,0]|[(1)*,0])] | [(1|[(0)*,1]|[(1)*,1]),(1|[(0)*,1]|[(1)*,1])]');
});
