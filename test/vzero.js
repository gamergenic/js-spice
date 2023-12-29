const expect = require('chai').expect;
const { spice } = require('..');

describe('vzero', function() {
  it('should indicate whether a 3-vector {\"x\":0, \"y\":0, \"z\":0} is the zero vector (true).', function() {

    let v = {"x":0, "y":0, "z":0};
    let actual = spice.vzero(v);
    let expected = true;

    expect(actual).to.equal(expected);
  });

  it('should indicate whether a 3-vector [0,0,0] is the zero vector (true).', function() {

    let v = [0, 0, 0];
    let actual = spice.vzero(v);
    let expected = true;

    expect(actual).to.equal(expected);
  });

  it('should indicate whether a 3-vector (0,0,0) is the zero vector (true).', function() {

    let actual = spice.vzero(0, 0, 0);
    let expected = true;

    expect(actual).to.equal(expected);
  });

  it('should indicate whether a 3-vector [0,0,0.01] is the zero vector (false).', function() {

    let v = [0, 0, 0.01];
    let actual = spice.vzero(v);
    let expected = false;

    expect(actual).to.equal(expected);
  });
});
