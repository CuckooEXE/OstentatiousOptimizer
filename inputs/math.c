int timestwo(int a )
{
  return a * 2;
}

int timesfour(int a)
{
  return timestwo(a) + timestwo(a);
}

int main(int argc, char *argv[]) {
  int a = 5;
  
  a = timestwo(a);
  a = timesfour(a);

  return a;
}