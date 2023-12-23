class MyVec {
  constructor(x, y) {
    this.x = x;
    this.y = y;
  }

  add(vec) {
    this.x += vec.x;
    this.y += vec.y;
  }

  getAdd(vec) {
    return new MyVector(this.x + vec.x, this.y + vec.y);
  }

  sub(vec) {
    this.x -= vec.x;
    this.y -= vec.y;
  }

  getSub(vec) {
    return new MyVector(this.x - vec.x, this.y - vec.y);
  }

  mul(scalar) {
    this.x *= scalar;
    this.y *= scalar;
  }

  getMul(scalar) {
    return new MyVector(this.x * scalar, this.y * scalar);
  }

  getDotProduct(vec) {
    return this.x * vec.x + this.y * vec.y;
  }
}

class MyMat extends Array {
  constructor(inValues) {
    super();
    if (typeof inValues !== "undefined") this.push(...inValues); // spread syntax to push all elements (and not the array itself)
  }

  static getIdentity() {
    return new MyMat([1, 0, 0, 0, 1, 0, 0, 0, 1]);
  }

  setValues(inValues) {
    this.splice(0); // remove all old values
    if (typeof inValues !== "undefined") this.push(...inValues); // spread syntax to push all elements (and not the array itself)
  }

  getValues() {
    return this.values();
  }

  mulPoint(inPoint) {
    let outPoint = [];
    for (let i = 0; i < 3; i++)
      outPoint.push(
        this[0 + i] * inPoint[0] + this[3 + i] * inPoint[1] + this[6 + i] * 1
      );
    return outPoint;
  }

  mulMat(mat) {
    let matWidth = mat.length;
    let outMat = new MyMat();
    for (let i = 0; i < matWidth; i += 3)
      for (let j = 0; j < 3; j++)
        outMat.push(
          this[0 + j] * mat[0 + i] +
            this[3 + j] * mat[1 + i] +
            this[6 + j] * mat[2 + i]
        );

    return outMat;
  }
}
