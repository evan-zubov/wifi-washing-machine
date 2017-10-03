String getLastJSONValue(String body, String key)
{
  int lastIndexOfUpdateId = body.lastIndexOf(key);
  int valueStartIndex = lastIndexOfUpdateId + key.length();
  int nextComaIndex = valueStartIndex;
  while (body[nextComaIndex] != ',' && body[nextComaIndex] != '}' && body[nextComaIndex] != ']' && nextComaIndex < body.length())
  {
    nextComaIndex++;
  }
  String result = body.substring(valueStartIndex, nextComaIndex);
  result.trim();
  return result;
}